#ifndef CODETREE_H
#define CODETREE_H

#include "FrequencyTable.h"
#include "StreamGuard.h"

#include <string>
#include <memory>

class CodeTree
{
private:
	struct Node
	{
		char ch_;
		CodeVector code_;
		std::weak_ptr<Node> p_;
		std::shared_ptr<Node> left_;
		std::shared_ptr<Node> right_;
		Node() : ch_(0), code_(), p_(), left_(nullptr), right_(nullptr) {};
		Node(std::shared_ptr<Node> p) : ch_(0), code_(), p_(p), left_(nullptr), right_(nullptr) {};
	};
	std::shared_ptr<Node> root_;

public:
	CodeTree() :root_(std::make_shared<Node>()) {}

	~CodeTree()
	{
		root_ = nullptr;
	}

	void assembleTree(const FrequencyTable& frequencyTable) 
	{
		size_t size = frequencyTable.getSize();
		for (size_t i = 0; i < size; i++)
		{
			std::shared_ptr<Node> x = root_;
			std::shared_ptr<Node> y = nullptr;
			size_t sizeS = frequencyTable[i].code_.getSize();
			for (size_t j = 0; j < sizeS; j++)
			{
				y = x;
				if (frequencyTable[i].code_[j] == 0)
				{
					x = x->left_;
					if (x == nullptr)
					{
						x = std::make_shared<Node>(y);
						y->code_.pushBack(0);
						x->code_ = y->code_;
						y->left_ = x;
					}
				}
				else
				{
					x = x->right_;
					if (x == nullptr)
					{
						x = std::make_shared<Node>(y);
						y->code_.pushBack(1);
						x->code_ = y->code_;
						y->right_ = x;
					}
				}
			}
			x->ch_ = frequencyTable[i].ch_;
			x->code_ = frequencyTable[i].code_;
		}
	}

	void getDecodedText(std::istream& in,std::ostream& out, const size_t& charCount) const
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return;
		}
		StreamGuard guard(in);
		size_t decodedCount = 0;
		std::shared_ptr<Node> x = root_;
		unsigned char byte = in.get();
		bool bit = 0;
		size_t bitCount = 0;
		while (decodedCount < charCount)
		{
			bit = byte & 1 << (7 - bitCount);
			if (bit)
			{
				x = x->right_;
			}
			else
			{
				x = x->left_;
			}
			if (x->ch_)
			{
				out << x->ch_;
				x = root_;
				decodedCount++;
			}
			bitCount++;
			if (bitCount == 8)
			{
				bitCount = 0;
				byte = in.get();
			}
		}
	}

	bool isLeaf(std::shared_ptr<Node> x) const
	{
		return x->left_ == nullptr && x->right_ == nullptr;
	}
};

#endif // !CODETREE_H