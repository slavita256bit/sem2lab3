# Component Selection and Design Review

Use this reference for substantive implementation or refactoring. Do not ask the
user to approve every routine choice or redesign architecture without a request.

## Choose a straightforward structure

For each new component, state the data/action it represents, who calls it, and how
it improves the existing solution. If the only answer is "cleaner" or "useful later,"
it probably is not needed yet.

Keep related data and rules in the domain class. Keep dialog steps in main or an
explicitly allowed module. Moving an overloaded main wholesale into interaction
moves complexity rather than removing it. Extract a real common operation while
leaving differences where they naturally belong.

Prefer a short switch when a few alternatives have different static types. Three
separate typed trees may be clearer than a shared tree with virtual wrappers.
However, three trees is one assignment's decision, not a mandatory architecture
for the next container. Do not embed domain names or sorting keys into this skill.

Learning objectives take priority over code reduction. If students must implement
an iterator, a standard generator does not satisfy that requirement. If only traversal
is needed and C++23 is approved, std::generator may remove a handwritten iterator.
Account for its single-pass semantics, range/tree lifetime, and possible coroutine
allocations; a short expression does not eliminate state or cost.

## Recheck technical traps observed in earlier work

- In coursework that already provides `String`, use its range and length.
  When one field per line is agreed, prefer bounded `getline` into a local
  `String` and return the value. Discard the rest of an oversized line before
  retrying. Ask before changing between line input and whitespace tokens.
  Avoid introducing `std::string` or `c_str()` just to validate a field.
- Use standard number conversion where it fits. With `from_chars`, check the
  result and that it reached the end, then apply the domain bounds. Share the
  read, parse, and retry loop for numeric types if only their value checks differ.
- Validate text against the agreed alphabet and character rules. Keep unused
  switches, encodings, and general-purpose policies out of the active path.
- Prefer a standard character predicate when it matches the specified alphabet
  and works with the input encoding. For a fixed alphabet, use direct range
  comparisons and isolated exceptions where possible. For UTF-8, a small helper
  can compare byte ranges using character literals as bounds. Avoid enumerating
  and scanning a whole alphabet for each letter, and avoid raw encoding masks
  in field validation. Use short, complete messages for fixed error buffers
  and a readable fallback for oversized messages.
- Trace reported unreachable branches to the operation that can fail, including
  implicit allocation failures. Remove redundant cleanup wrappers when ownership
  can be established at allocation. Verify the failure path before dropping cleanup.
- Use `noexcept` for an actual exception guarantee, not to silence a diagnostic.
  Account for allocations, stream operations, and calls into generic types.
- vector<Base> slices derived objects; typeid cannot restore discarded fields.
  A fixed-length Base array has the same issue. Resolve value storage, polymorphism,
  and ownership requirements before selecting the container.
- Container<Derived> does not inherit from Container<Base>. A pointer cast does
  not provide a shared container interface; reinterpret_cast is not a substitute.
- A free operator<< is not virtual: overload selection follows the static type.
  Use a known concrete type or an appropriate virtual operation. Do not introduce
  RTTI dispatch when the container already knows T.
- A reverse static_cast through a virtual base is not appropriate. Choose casts
  for the actual hierarchy. Directly dereferencing dynamic_cast is acceptable only
  when a proven invariant guarantees its result; do not generalize a request to
  remove checks in one example to arbitrary untrusted data.
- h/tpp makes template definitions visible at use sites. Do not also leave old cpp
  definitions and explicit-instantiation lists. Do not promise an arbitrary T if
  invoked methods require print_header, <<, or comparisons.
- Equivalent ordering keys and full object equality differ. With duplicate keys,
  verify selection, lookup, and deletion of the right object, not only sorted output.

## Define ownership and mutation order explicitly

For each pointer, identify its owner and when ownership transfers. Do not pass a
local object's address to an owning container or transfer one pointer twice.
Deletion needs understandable empty/leaf/one-child/two-child behavior; a released
node must not retain ownership of transferred links. A superficial nullptr check
does not fix use-after-free: correct the lifetime itself.

When a key changes, preserve container ordering by editing a copy and relocating
the entry or using another agreed protocol. With exceptions, choose an order that
preserves the original when input or allocation fails. Do not carry an earlier
lab's exception prohibition into an exception-handling assignment. Do not promise
a preservation guarantee without checking failure paths and cleanup.

## Scale final verification to the task

For containers/manual ownership, select applicable scenarios: empty state, first/last
entry, duplicate keys, reordering, root deletion, repeated clear, insertion after
removal, and exit. For validated input, check recovery, boundaries, EOF, and original
data preservation. Do not run this entire matrix for a comment adjustment.

Inspect real clangd/CLion warnings in affected files. Do not claim IDE verification
when only a compiler was run; name the actual tool. For template/ODR changes, verify
inclusion from multiple cpp files. For refactoring, compare observable behavior before
and after; for a semantic change, test the new behavior instead of demanding identical
old output.

When the student points out a local issue, search the active project for the same
underlying pattern. Check nearby code, analogous fields and call sites, paired
operations, and sibling classes. Fix confirmed equivalents in the same pass,
unless the student explicitly limits the scope. For example, check other repeated
field labels after extracting one into a named constant, or review both increment
and decrement after switching one to `begin()` and `end()`. Preserve cases whose
technical requirements differ, and summarize the related fixes.

Stop once the agreed behavior works, suitable checks pass, formatting has been
reviewed, and current documentation matches the code. Do not add architectural
layers on a final pass just for completeness.
