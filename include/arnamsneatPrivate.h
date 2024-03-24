
#pragma once

#ifdef __clang__
#   define AMST_NULLABLE _Nullable
#   define AMST_NONNULL _Nonnull
#else
#   define AMST_NULLABLE
#   define AMST_NONNULL
#endif
