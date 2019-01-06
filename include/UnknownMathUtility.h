#ifndef UNKNOWN_MATH_UTILITY_H
#define UNKNOWN_MATH_UTILITY_H
#include <memory>
namespace UnknownMath {
	inline void* AllocateAligned(size_t n);
	inline void FreeAligned(void* p);
}

#define UNKNOWN_MATH_ALIGNMENT 16

#define UNKNOWN_MATH_OPERATION_LOOP(times, op) \
{ \
	for(int i = 0; i < times; ++i) { \
		op; \
	} \
} \

#define UNKNOWN_MATH_STATIC_ALIGNMENT_NEW \
static void* operator new (size_t count) { \
	return UnknownMath::AllocateAligned(count); \
} \
static void* operator new[](size_t count) { \
	return UnknownMath::AllocateAligned(count); \
} \
static void* operator new (size_t, void* ptr) { return ptr; } \
static void* operator new[](size_t, void* ptr) { return ptr; } \
static void operator delete(void* ptr) { UnknownMath::FreeAligned(ptr); } \
static void operator delete[](void* ptr) { UnknownMath::FreeAligned(ptr); } \
static void operator delete(void*, void*) {} \
static void operator delete[] (void*, void*) {} \

namespace UnknownMath {
	// Reference Google/Mathfu
	inline void *AllocateAligned(size_t n) {
		size_t needSpace = n + UNKNOWN_MATH_ALIGNMENT;
		void* ptr = malloc(needSpace);
		void* originalPtr = ptr;
		if (std::align(UNKNOWN_MATH_ALIGNMENT, n, ptr, needSpace)) {
			if (originalPtr == ptr) {
				uint8_t* tptr = reinterpret_cast<uint8_t*>(ptr);
				tptr += UNKNOWN_MATH_ALIGNMENT;
				*(reinterpret_cast<uint8_t**>(tptr) - 1) = reinterpret_cast<uint8_t*>(ptr);
				return tptr;
			}
			else {
				// 由于cl和gcc对malloc返回的内存地址都进行限制，一般而言已经是16字节对齐的
				// 所以这部分代码很少会运行
				uint8_t* tptr = reinterpret_cast<uint8_t*>(ptr);
				uint8_t* optr = reinterpret_cast<uint8_t*>(originalPtr);
				if (static_cast<size_t>(tptr - optr) >= sizeof(void*)) {
					*(reinterpret_cast<uint8_t**>(tptr) - 1) = optr;
					return tptr;
				}
				else {
					free(originalPtr);
					return nullptr;
				}
			}
		}
		free(ptr);
		return nullptr;
	}

	inline void FreeAligned(void *p) {
		if (p == NULL) return;
		free(*(reinterpret_cast<uint8_t **>(p) - 1));
	}

	template<typename T>
	struct AlignedAllocator {
		typedef T value_type;
		AlignedAllocator() noexcept {}

		template<typename U> AlignedAllocator(const AlignedAllocator<U>&) noexcept {}
		template<typename U> bool operator==(const AlignedAllocator<U>&) const noexcept { return true; }
		template<typename U> bool operator!=(const AlignedAllocator<U>&) const noexcept { return false; }
		T* allocate(const size_t n) const {
			return reinterpret_cast<T*>(AllocateAligned(n * sizeof(T)));
		}
		void deallocate(T* ptr, size_t) { FreeAligned(ptr); }
	};
}

#endif // UNKNOWN_MATH_UTILITY_H
