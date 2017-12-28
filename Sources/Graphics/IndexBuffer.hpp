#ifndef NU_INDEXBUFFER_HPP
#define NU_INDEXBUFFER_HPP

#include "../Application/GLEWWrapper.hpp"

namespace nu
{

class IndexBuffer
{
	public:
		IndexBuffer();
		~IndexBuffer();

		void set(U32* indices, U32 size);
		void set(const std::vector<U32>& indices);

		void bind();

		U32 getIndices() const;

		bool isValid() const;
		U32 getId() const;

	private:
		U32 mIndex;
		U32 mIndices;
};

} // namespace nu

#endif // NU_INDEXBUFFER_HPP