# (1) Safety

- Zero Technical Debt: Fix issues immediately. Never rely on future refactoring.
- Assert Aggressively: Validate inputs, outputs, tensor shapes and invariants in every function.
- Pair Assertions: Check critical data at multiple points to catch internal inconsistencies.
- Bounded Execution: Set fixed upper limits on all loops, queues, and recursion depth (especially for graph traversal).
- Fail Fast: Detect unexpected conditions immediately. Crash rather than corrupt state.
- No Undefined Behavior: Rely on explicit code, not compiler optimizations. Treat all compiler warnings as errors.
- Controlled Memory:
    - Strongly prefer static allocation over dynamic allocation.
    - When dynamic allocation is necessary (e.g., graph construction), use arenas or memory pools*
    - Enforce strict upper bounds on memory usage.
    - Assert Allocation: Wrap every arena allocation, `malloc`, or resource claim in an assert (e.g., `assert(ptr != NULL)`).
- Explicit Mutation: Avoid manipulating function arguments or causing side effects. If copying has an extremely high memory cost, mutation is allowed but the function must be named with a suffix (`_mut`) and mutation must be obvious in the naming (e.g., `out_result`).
- Testing:
      - Mandatory Unit Tests: Every new feature must be accompanied by unit tests.
      - Coverage: The more tests, the better. Cover edge cases, boundary conditions and failure modes.

# (2) Quality

- Obvious Code > Clever Code
- Maximize Locality: Keep related code together. Define things near usage. Minimize variable scope.
- Centralize Control Flow: Branching logic belongs in parents. leaf functions should be pure logic.
- Guard Clauses: Handle checks first, return early, minimize nesting.
- Functions: Do one coherent thing (ideally <70 lines). Prefer lambdas/inline logic over tiny single-use functions.
- Decompose Conditionals: Use named variables to simplify complex `if` conditions.
- Comments: Comments explain *why*, not *what*. Use lowercase single lines. ASCII illustrations are welcome.
- Functional Style: Prefer pure functions (data in, data out) and immutability for logic.

C++ Specific:

- Structs over Classes: Strictly separate data from logic. Use struct for pure data containers (PODs) and stateless functions within namespaces for behavior. Avoid inheritance and member functions.
- Explicit Fixed-Width Types: Use `std::int32_t`, `std::uint64_t`, etc. Ban implementation-dependent types like `int`, `long` or `unsigned`.
- Modern I/O: Use `fmt::print` (or C++23 `std::print`) exclusively. Avoid `std::cout` and stream operators `<<`.
- Strict Const Correctness: Everything is `const` by default (variables, pointers, arguments). Only remove `const` when mutation is the specific intent. Prefer `constexpr` for constants known at compile time.
- String Views: Prefer `std::string_view` over `const std::string&` for function arguments to avoid unnecessary allocations.
- No C-Style Casts: Ban `(type)value`. Use `static_cast`, `reinterpret_cast`, or `std::bit_cast` to make conversion intent explicit and grep-able.
- Null Safety: Prefer references (`T&`) over pointers (`T*`) when a value must exist. Use `std::optional` or `T*` only when "no value" is a valid state.
- Container Defaults: Default to `std::vector` for sequences. Avoid `std::list` or `std::map` unless pointer stability or specific lookup characteristics are strictly required.
- Avoid `auto`: Explicitly state types for readability, unless the type is unspellable (lambdas) or blatantly obvious (iterators).
- Header Hygiene: `#include` exactly what you use. Use `#pragma once`.

# (3) Performance

- Follow Data-Oriented Design (DoD) principles
- Design for Hardware: Organize data to match how the hardware reads it (cache lines).
- Struct of Arrays (SoA): Prefer SoA over Array of Structs (AoS) for heavy computation to maximize SIMD usage.
- Data Alignment: Ensure critical data is aligned (e.g., 64 bytes) for SIMD efficiency. Assert alignment on access.
- Batch Processing: Write functions that transform arrays of data rather than single elements (data transformation > object interaction).
- Existence-based Processing: Filter data *before* processing so loops run on contiguous, valid data (avoid `if (obj->active)` inside hot loops).

Based on https://tigerstyle.dev/
