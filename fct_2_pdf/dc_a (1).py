# -*- coding: utf-8 -*-
Q = []

Q.append({
"q": "Consider T(n) = 2T(n/2) + n log n. Using the extended Master theorem (Case 2 with a polylog factor), what is T(n)?",
"opts": ["Θ(n log n)", "Θ(n log&sup2; n)", "Θ(n&sup2;)", "Θ(n log n log log n)"],
"ans": 1,
"exp": "Here a=2, b=2, so n<sup>log_b a</sup> = n. f(n) = n log n = n&sup1;&middot;log&sup1;n, matching the extended Master theorem's Case 2 (f(n) = Θ(n<sup>log_b a</sup>&middot;log<sup>k</sup>n) with k=1), giving T(n) = Θ(n<sup>log_b a</sup>&middot;log<sup>k+1</sup>n) = Θ(n log&sup2; n). (A) is the answer for the plain recurrence 2T(n/2)+n without the extra log factor &mdash; picking the 'simpler-looking' option is a common trap. (C) wildly overestimates by ignoring the actual computation of n<sup>log_b a</sup>. (D) invents a log log n term that does not arise from this recurrence's structure at all."
})

Q.append({
"q": "What is the tightest asymptotic bound for T(n) = 3T(n/4) + n log n, by the Master theorem?",
"opts": ["Θ(n log n)", "Θ(n<sup>log&#8324; 3</sup>)", "Θ(n<sup>log&#8324; 3</sup> log n)", "Θ(n&sup2;)"],
"ans": 0,
"exp": "a=3, b=4, so n<sup>log_4 3</sup> &asymp; n<sup>0.79</sup>. Since f(n) = n log n grows polynomially faster than n<sup>0.79</sup> (f(n) = &Omega;(n<sup>log_4 3 + &epsilon;</sup>) for some &epsilon;&gt;0), and the regularity condition a&middot;f(n/b) &le; c&middot;f(n) holds, this is Case 3, giving Θ(n log n) &mdash; the driving function dominates. (B) is correct only if f(n) were absent entirely (T(n)=3T(n/4) alone), a classic distractor from forgetting the additive term. (C) incorrectly blends Case 2's log-multiplier onto a Case 3 scenario. (D) massively overestimates the true growth rate."
})

Q.append({
"q": "In Karatsuba's algorithm for multiplying two n-digit numbers, three recursive multiplications of (n/2)-digit numbers are combined with O(n) extra work. What recurrence and complexity result?",
"opts": ["T(n) = 3T(n/2) + O(n), Θ(n<sup>1.585</sup>)", "T(n) = 4T(n/2) + O(n), Θ(n&sup2;)", "T(n) = 3T(n/2) + O(n&sup2;), Θ(n&sup2;)", "T(n) = 2T(n/2) + O(n), Θ(n log n)"],
"ans": 0,
"exp": "Karatsuba reduces 4 naive multiplications to 3 via algebraic manipulation (computing (a+b)(c+d) and subtracting known products), giving T(n) = 3T(n/2) + O(n). By the Master theorem, a=3, b=2, so n<sup>log&#8322; 3</sup> &asymp; n<sup>1.585</sup> dominates the O(n) term (Case 1), giving T(n) = Θ(n<sup>1.585</sup>). (B) is the naive grade-school recurrence before Karatsuba's optimization &mdash; the entire point of Karatsuba is avoiding that 4th multiplication. (C) incorrectly inflates the combine step to O(n&sup2;), which would erase the benefit of reducing the multiplication count. (D) is the merge-sort recurrence shape, structurally unrelated to Karatsuba's 3-way split."
})

Q.append({
"q": "Strassen's algorithm multiplies two n&times;n matrices using 7 multiplications of (n/2)&times;(n/2) submatrices plus O(n&sup2;) additions. What is its time complexity, and why does it beat the naive 8-multiplication approach?",
"opts": ["Θ(n&sup3;), because 8 recursive calls also give n&sup3; so there is no real gain", "Θ(n<sup>log&#8322; 7</sup>) &asymp; Θ(n<sup>2.807</sup>), strictly better than Θ(n&sup3;) for large n", "Θ(n&sup2; log n), because the additions dominate asymptotically", "Θ(n<sup>2.5</sup>), the geometric mean of n&sup2; and n&sup3;"],
"ans": 1,
"exp": "With a=7, b=2: T(n) = 7T(n/2) + O(n&sup2;) solves to Θ(n<sup>log&#8322; 7</sup>) = Θ(n<sup>2.807...</sup>) by Master theorem Case 1, since log&#8322;7 &asymp; 2.807 &gt; 2 means the recursive term dominates the O(n&sup2;) combine work. This beats the naive Θ(n&sup3;) obtained from 8 recursive multiplications (T(n)=8T(n/2)+O(n&sup2;) = Θ(n&sup3;) since log&#8322;8 = 3). (A) falsely claims 8 multiplications also yield n&sup3; 'with no gain' &mdash; they do yield n&sup3;, but that IS worse than Strassen's 2.807 exponent, so the reasoning is backwards. (C) invents a log factor not implied by Case 1. (D) is a fabricated 'averaging' heuristic with no grounding in the Master theorem."
})

Q.append({
"q": "What does the recurrence T(n) = 2T(n/2) + Θ(1) describe, and what is its solution?",
"opts": ["A balanced divide-and-conquer with constant combine time (e.g., counting nodes in a balanced binary tree); T(n) = Θ(n)", "Binary search; T(n) = Θ(log n)", "Merge sort; T(n) = Θ(n log n)", "This recurrence is invalid because combine work must be at least linear"],
"ans": 0,
"exp": "By the Master theorem: a=2, b=2, n<sup>log&#8322;2</sup> = n. f(n)=Θ(1) is polynomially smaller than n (Case 1), so T(n) = Θ(n). This matches problems like counting nodes in a balanced binary tree, where each call does O(1) work but there are Θ(n) total calls. (B) confuses this with T(n)=T(n/2)+Θ(1) (a single recursive call, not two), which gives binary search's Θ(log n) &mdash; swapping one recursive call for two changes the answer entirely. (C) is the merge sort recurrence T(n)=2T(n/2)+Θ(n), which has linear (not constant) combine work. (D) is false; recurrences with sub-linear combine steps are common and perfectly valid."
})

Q.append({
"q": "For T(n) = T(n/3) + T(2n/3) + O(n) analyzed via a recursion tree, what is the depth of the longest root-to-leaf path, and why does the O(n log n) bound still hold despite the tree being unbalanced?",
"opts": ["Depth is log<sub>3/2</sub> n (from repeatedly taking the 2n/3 branch); the bound holds because every level of the tree still sums to exactly cn in total work", "Depth is log&#8323; n (from the n/3 branch only); the bound is therefore not tight", "Depth is constant; the recurrence solves to O(n)", "Depth is n; the recurrence solves to O(n&sup2;)"],
"ans": 0,
"exp": "The tree is unbalanced: the shortest path (always taking n/3) has length log&#8323; n, but the longest path (always taking 2n/3) has length log<sub>3/2</sub> n. Crucially, every level &mdash; despite the imbalance in branch sizes &mdash; sums to exactly cn (since the two children's sizes always add to n), and there are at most log<sub>3/2</sub> n levels, giving total cost O(n log n), matching the substitution-method proof. (B) accounts for only the shorter path, underestimating the tree's true depth. (C) and (D) misunderstand unbalanced-but-still-logarithmic recursion: the imbalance doesn't collapse the depth to constant, nor does per-level work blow up to make the bound quadratic."
})

Q.append({
"q": "Which is the correct description of the substitution method's inductive step for proving T(n) &le; cn log n, where T(n) = 2T(&lfloor;n/2&rfloor;) + n?",
"opts": ["Assume T(k) &le; ck log k for all k &lt; n, substitute k = &lfloor;n/2&rfloor;, then algebraically show the resulting expression is &le; cn log n for suitable c &gt; 0, n &ge; n&#8320;", "Assume T(n) &le; cn log n for the very n being proved, then it trivially holds", "Prove only the base case T(1) = Θ(1) and conclude the guess holds for all n", "Substitute the guess into the recurrence and solve for n directly using algebra, without induction"],
"ans": 0,
"exp": "The substitution method uses strong induction: assume the bound holds for all smaller values (the hypothesis), substitute into the recurrence, and show algebraically that the bound then holds for n &mdash; often requiring subtraction of a lower-order term to absorb slack, plus separate verification of the base case(s). (B) is circular reasoning: you cannot assume what you are trying to prove for the same n. (C) is incomplete; the base case says nothing about the inductive step, where the real work (handling the +n term) happens. (D) misdescribes the method; there is no direct algebraic 'solving for n' &mdash; it is a proof technique, not equation-solving."
})

Q.append({
"q": "For T(n) = T(&lfloor;n/2&rfloor;) + T(&lceil;n/2&rceil;) + 1, a naive guess T(n) &le; cn fails the substitution-method induction. What is the standard fix, and what is the true asymptotic bound?",
"opts": ["Strengthen the guess to T(n) &le; cn &minus; b for constant b &gt; 0 to absorb the slack from the +1 term; the true bound remains Θ(n)", "Switch to an O(n&sup2;) guess since O(n) must be structurally wrong", "Add a multiplicative log factor, guessing T(n) &le; cn log n instead", "Increase c without bound until the inequality eventually holds"],
"ans": 0,
"exp": "This is CLRS's classic 'subtract a lower-order term' technique: naively substituting T(n) &le; cn into T(n) &le; c&lfloor;n/2&rfloor; + c&lceil;n/2&rceil; + 1 = cn + 1 fails due to the extra +1. Strengthening to T(n) &le; cn &minus; b lets the &minus;b terms combine to cancel the +1, so induction succeeds, and the asymptotic bound remains Θ(n). (C) is wrong: this recurrence solves to Θ(n), not Θ(n log n), since there is no per-level combine cost scaling with n (unlike merge sort's Θ(n) combine step). (B) is a non-sequitur; a failed proof attempt for a linear guess doesn't imply quadratic growth. (D) doesn't work: no matter how large c is, cn + 1 &le; cn is always false &mdash; the fix is structural (subtracting a constant), not a larger constant factor on the same form."
})

Q.append({
"q": "Given T(n) = 4T(n/2) + n, what is Θ(T(n)) and which Master theorem case applies?",
"opts": ["Case 1 (recursive term dominates): Θ(n&sup2;)", "Case 2 (balanced): Θ(n&sup2; log n)", "Case 3 (driving function dominates): Θ(n)", "Case 1, but the correct value is Θ(n log n)"],
"ans": 0,
"exp": "a=4, b=2 &rarr; n<sup>log&#8322;4</sup> = n&sup2;. f(n)=n is polynomially smaller than n&sup2; (n = O(n<sup>2&minus;&epsilon;</sup>) for &epsilon;=1), satisfying Case 1, so T(n) = Θ(n&sup2;). (B) misapplies Case 2, which requires f(n) = Θ(n<sup>log_b a</sup>) exactly (here that would mean f(n)=Θ(n&sup2;), but f(n)=n is not) &mdash; a frequent error is assuming any 'close-looking' exponent lands in Case 2. (C) inverts which function dominates; f(n)=n is smaller, not larger, than n<sup>log_b a</sup>=n&sup2;, so Case 3 cannot apply. (D) gets the case number right but the final value wrong, revealing confusion about computing n<sup>log_b a</sup> for a=4, b=2 (which is n&sup2;, not n log n)."
})

Q.append({
"q": "Which recurrence CANNOT be solved directly by the basic (non-extended) Master theorem as stated in CLRS, and why?",
"opts": ["T(n) = 2T(n/2) + n/log n, because f(n) is asymptotically smaller than n but not by a polynomial factor", "T(n) = 3T(n/3) + n, because a = b", "T(n) = T(n/2) + 1, because a = 1", "T(n) = 2T(n/2) + n&sup2;, because f(n) dominates polynomially"],
"ans": 0,
"exp": "The Master theorem requires f(n) to be polynomially smaller, polynomially larger (with the regularity condition), or polynomially equal (within log factors, per the extended version) to n<sup>log_b a</sup>. Here f(n) = n/log n is smaller than n=n<sup>log&#8322;2</sup> but not by a polynomial factor (n / (n/log n) = log n, which grows slower than any n<sup>&epsilon;</sup>), falling into a gap the basic Master theorem doesn't cover &mdash; it needs more advanced tools like the Akra&ndash;Bazzi method. (B) is a standard Case 2 application (a=b=3, f(n)=n=n<sup>log&#8323;3</sup>), giving Θ(n log n), with no gap at all. (C) is the classic binary search recurrence, solved directly by Case 2, giving Θ(log n). (D) is squarely Case 3 (f(n)=n&sup2; dominates n<sup>log&#8322;2</sup>=n polynomially), solvable directly, giving Θ(n&sup2;)."
})

Q.append({
"q": "In merge sort's MERGE procedure using sentinel values (&infin;) at the ends of each subarray, what goes wrong if the sentinels are omitted without adding explicit bounds-checking logic?",
"opts": ["The merge loop may read past the end of an exhausted subarray, since comparisons continue against a nonexistent element once one side runs out", "The algorithm still works correctly but degrades to Θ(n&sup2;) time", "The algorithm silently produces a correctly sorted array with no side effects", "The recursion never terminates"],
"ans": 0,
"exp": "Sentinels let the merge loop's comparison stay well-defined without a separate 'copy remaining elements' step. Without them and without alternative bounds-checking, once one subarray is fully consumed, the loop keeps comparing against an out-of-range index &mdash; undefined behavior or an explicit crash depending on the language. (B) is wrong; this is a correctness/safety bug, not merely a performance regression. (C) is false &mdash; this is precisely the kind of subtle bug that corrupts output or crashes rather than being benign. (D) confuses an indexing bug with non-termination; MERGE is not recursive, and MERGE-SORT's recursion terminates via shrinking subarray size regardless of any bug inside MERGE."
})

Q.append({
"q": "In the divide-and-conquer maximum-subarray algorithm, the crucial extra step is finding the max crossing subarray. What is its time complexity for a subarray of size n, and why?",
"opts": ["Θ(n), via two separate linear scans outward from the midpoint (one leftward, one rightward)", "Θ(log n), via binary search on both halves", "Θ(n log n), because it recursively finds crossing subarrays too", "Θ(1), because the midpoint value alone determines the crossing max"],
"ans": 0,
"exp": "FIND-MAX-CROSSING-SUBARRAY scans leftward from mid to find the best left extension, then rightward from mid+1 for the best right extension &mdash; two linear, non-recursive passes, Θ(n) total. This step is exactly why the overall recurrence is T(n) = 2T(n/2) + Θ(n), matching merge sort's shape. (B) wrongly assumes crossing sums are monotonic enough for binary search; they are not, so every boundary extension must be examined. (C) incorrectly makes the crossing step itself recursive; only the two half-subarray searches recurse, the crossing step is separate and linear. (D) drastically underestimates the work; the best crossing point cannot be found without scanning outward from the midpoint."
})

Q.append({
"q": "What is the overall recurrence and complexity of the divide-and-conquer maximum-subarray algorithm, and how does it compare to Kadane's algorithm?",
"opts": ["T(n) = 2T(n/2) + Θ(n) = Θ(n log n); Kadane's Θ(n) is asymptotically better", "T(n) = 2T(n/2) + Θ(1) = Θ(n); identical to Kadane's approach", "T(n) = T(n/2) + Θ(n) = Θ(n); identical to Kadane's approach", "T(n) = 2T(n/2) + Θ(n&sup2;) = Θ(n&sup2;); worse than brute force"],
"ans": 0,
"exp": "As established, the crossing-subarray step costs Θ(n), giving the merge-sort-shaped recurrence T(n) = 2T(n/2) + Θ(n) = Θ(n log n) by Master theorem Case 2. This is asymptotically worse than Kadane's Θ(n) DP approach, though CLRS presents the D&C version pedagogically before introducing the faster linear algorithm. (B) wrongly treats the crossing step as constant time, which would require somehow knowing the max crossing sum without scanning. (C) mismodels the recursion with only one recursive call instead of two (D&C searches both halves). (D) fabricates a worse-than-brute-force outcome; Θ(n log n) is strictly better than the Θ(n&sup2;) brute-force approach."
})

Q.append({
"q": "In the closest-pair-of-points D&C algorithm, why does the 'strip' merge step examine only a constant number of candidate points per point, rather than all points in the strip?",
"opts": ["A geometric packing argument shows that within the y-sorted strip, only a small constant number of subsequent points can possibly be closer than &delta; to any given point, since the recursive &delta; already bounds minimum spacing in each half", "The algorithm deliberately ignores boundary points for simplicity, accepting approximate results", "All points in the strip are automatically guaranteed to be within &delta; of each other", "A hash table lookup in O(1) replaces the need for pairwise comparisons"],
"ans": 0,
"exp": "The key lemma: if strip points are sorted by y-coordinate, any point has at most a small constant number of subsequent strip points (a well-known bound, often stated as at most 7) that could possibly be closer than &delta; &mdash; because points closer than &delta; to each other cannot be packed too densely into a &delta;&times;2&delta; region without violating that &delta; is already the minimum distance within each recursive half. This keeps the merge step at Θ(n), giving overall Θ(n log n). (B) is false; the classical closest-pair algorithm is exact, not approximate. (C) overstates the guarantee: being in the strip only means being within &delta; horizontally of the dividing line, not close to every other strip point. (D) fabricates a mechanism; no hashing is involved &mdash; the bound is purely geometric."
})

Q.append({
"q": "What is the time complexity of the closest-pair-of-points algorithm when the y-sorted strip order is maintained via a linear-time merge at each recursive level (rather than re-sorting)?",
"opts": ["Θ(n log n)", "Θ(n log&sup2; n)", "Θ(n&sup2;)", "Θ(n)"],
"ans": 0,
"exp": "Maintaining y-sorted order via merging (like merge sort's merge step) rather than re-sorting at every level gives the recurrence T(n) = 2T(n/2) + Θ(n), which solves to Θ(n log n) &mdash; the standard, optimized version. (B) results from the naive variant that re-sorts the strip by y-coordinate at every level using an O(n log n) sort, giving T(n) = 2T(n/2) + Θ(n log n); this is valid but suboptimal, and a very common 'almost right' distractor. (C) would only occur with a brute-force all-pairs approach, defeating the purpose of divide-and-conquer. (D) is impossible for comparison-based geometric closest-pair at this level of generality."
})

Q.append({
"q": "A student claims: 'Any divide-and-conquer algorithm that splits a problem of size n into 2 subproblems of size n/2 must run in Θ(n log n) time.' Is this correct?",
"opts": ["No &mdash; complexity also depends critically on the combine step's cost; e.g., 2T(n/2)+Θ(1) gives Θ(n), while 2T(n/2)+Θ(n&sup2;) gives Θ(n&sup2;)", "Yes, this follows directly from the Master theorem regardless of the combine cost", "No, because the number of subproblems must always be a power of 2 for the theorem to apply", "Yes, because two half-size subproblems always implies balanced logarithmic depth, which fixes the total to n log n"],
"ans": 0,
"exp": "This is a critical trap: fixing a=2, b=2 only fixes n<sup>log_b a</sup> = n; the overall complexity depends entirely on how f(n) (the combine cost) compares to n. With f(n)=Θ(1), Case 1 gives Θ(n); with f(n)=Θ(n), Case 2 gives Θ(n log n) (merge sort); with f(n)=Θ(n&sup2;), Case 3 gives Θ(n&sup2;). (B) is false precisely because it ignores this dependency &mdash; the Master theorem's entire mechanism is comparing f(n) to n<sup>log_b a</sup>. (C) is a fabricated constraint; a and b need not be powers of 2, though non-integer subdivision requires floor/ceiling handling. (D) repeats the same flawed logic just rephrased &mdash; logarithmic depth alone doesn't fix per-level cost."
})

Q.append({
"q": "For recursive binary search, what is the recurrence, and what subtle bug can arise from computing the midpoint as (low+high)/2 rather than low+(high&minus;low)/2 in a fixed-width-integer language?",
"opts": ["T(n) = T(n/2) + Θ(1) = Θ(log n); low+high can overflow for large indices, producing an incorrect (possibly negative) midpoint", "T(n) = 2T(n/2) + Θ(1) = Θ(n); there is no overflow risk since indices are always small", "T(n) = T(n/2) + Θ(1) = Θ(log n); the two formulas are always numerically identical, so there is no bug", "T(n) = T(n&minus;1) + Θ(1) = Θ(n); overflow causes linear-time degradation"],
"ans": 0,
"exp": "Binary search makes one recursive call on a half-sized problem plus constant work, giving T(n) = T(n/2) + Θ(1) = Θ(log n) by Master theorem Case 2 (a=1, b=2, f(n)=Θ(1)=n<sup>log&#8322;1</sup>=n&#8304;). The famous documented bug (even seen in production Java) is that low+high can exceed the maximum representable integer when both are large, silently overflowing and corrupting the midpoint; low+(high&minus;low)/2 avoids ever summing two large values. (B) wrongly doubles the recursive calls; binary search discards half the array and recurses on only one side. (C) is factually wrong about the bug &mdash; the formulas are mathematically equal in infinite precision but NOT identical under fixed-width overflow, which is the entire point. (D) misapplies both the recurrence and the bug's consequence &mdash; overflow corrupts an index; it doesn't degrade the algorithm to linear time."
})

Q.append({
"q": "What is the recurrence and complexity for the naive recursive Fibonacci computation F(n)=F(n&minus;1)+F(n&minus;2), and why is it NOT considered efficient divide-and-conquer?",
"opts": ["T(n) = T(n&minus;1) + T(n&minus;2) + Θ(1) &asymp; Θ(&phi;<sup>n</sup>) (exponential); it's inefficient because subproblems overlap massively rather than being independent", "T(n) = 2T(n/2) + Θ(1) = Θ(n); it's inefficient only due to constant-factor overhead", "T(n) = T(n/2) + Θ(1) = Θ(log n); it is actually very efficient", "T(n) = T(n&minus;1) + Θ(1) = Θ(n); it is already efficient and optimal"],
"ans": 0,
"exp": "Naive Fibonacci branches into two calls of size n&minus;1 and n&minus;2 &mdash; a decrease-by-constant (not divide-by-fraction) recursion, and because the subproblems overlap massively (F(n&minus;2) is recomputed independently within both the F(n&minus;1) and F(n) call trees), total work grows exponentially, approximately Θ(&phi;<sup>n</sup>) where &phi; is the golden ratio (&asymp;1.618). This motivates why memoization/DP (exploiting overlapping subproblems) beats naive recursion &mdash; true efficient divide-and-conquer assumes independent, non-overlapping subproblems. (B) and (C) incorrectly model this as size-halving recursion, but Fibonacci's recursion reduces size by a constant amount, so the Master theorem doesn't even apply in that form. (D) drastically underestimates the branching factor; there are two recursive calls, not one, which is exactly what drives the exponential blowup."
})

Q.append({
"q": "In quickselect (D&C-based selection with expected linear time), what is the WORST-case complexity, and under what condition does it occur with a naive 'always pick the last element' pivot strategy?",
"opts": ["Θ(n&sup2;), when the input is already sorted (or reverse-sorted), causing maximally unbalanced partitions at every step", "Θ(n log n), on random inputs, matching quicksort's average case", "Θ(n), always, because selection only requires one recursive call regardless of pivot quality", "Θ(log n), because only one side of the partition is ever recursed into"],
"ans": 0,
"exp": "With a naive last-element pivot on already-sorted (or reverse-sorted) input, every partition step splits off just one element, leaving a subproblem of size n&minus;1 &mdash; giving T(n) = T(n&minus;1) + Θ(n) = Θ(n&sup2;), the worst case. Even though quickselect recurses into only one side (unlike quicksort's two), a consistently unbalanced split still produces quadratic behavior because the linear partition cost is paid n times over a linearly-shrinking sequence of sizes. (B) misattributes Θ(n log n) &mdash; that's quicksort's average-case complexity, not quickselect's (quickselect's expected case is Θ(n), better than quicksort's, since it discards one side). (C) is false; a single recursive call doesn't guarantee good complexity if the partition itself is unbalanced &mdash; the pivot quality matters enormously. (D) is wrong; only one side IS recursed into (that part is true of quickselect), but that alone doesn't make it Θ(log n) since the sizes can shrink by only 1 each time rather than halving."
})

Q.append({
"q": "Randomized quickselect selects a uniformly random pivot at each step. What is its expected time complexity, and why does randomization help despite the existence of a Θ(n&sup2;) worst case?",
"opts": ["Θ(n) expected; randomization ensures that, on average, partitions are reasonably balanced, and adversarial worst-case inputs cannot be constructed in advance since the pivot choice is unknown to any fixed input", "Θ(n log n) expected; matches merge sort exactly regardless of pivot choice", "Θ(n&sup2;) expected; randomization doesn't change the expected complexity, only the variance", "Θ(1) expected; random pivots always land exactly on the median"],
"ans": 0,
"exp": "With a uniformly random pivot, the expected recurrence sums geometrically decreasing subproblem sizes across possible pivot ranks, yielding E[T(n)] = Θ(n) &mdash; a classic result proved via indicator random variables (similar to randomized quicksort's analysis, but selection needs only one recursive branch, improving the constant). Crucially, no fixed input sequence can force the worst case every time, because the pivot is chosen independently of the input at each call, so an adversary who doesn't see the random choices in advance cannot construct a guaranteed bad case. (B) is wrong; quickselect's expected complexity is linear, strictly better than n log n. (C) misunderstands the effect of randomization; it does change the expected complexity dramatically (from potentially always-quadratic with adversarial fixed pivots to linear in expectation) — it's not merely a variance reduction. (D) is false; random pivots don't guarantee landing on the median; they only guarantee good behavior on average across the randomness."
})

Q.append({
"q": "The deterministic median-of-medians algorithm guarantees Θ(n) worst-case selection by choosing pivots via groups of 5. What recurrence captures its worst-case behavior, and why is group size exactly 5 significant?",
"opts": ["T(n) &le; T(n/5) + T(7n/10) + Θ(n); group size 5 is the smallest odd size that guarantees at least ~30% of elements are provably smaller (and 30% larger) than the chosen pivot, keeping both recursive calls' combined size below n", "T(n) &le; 2T(n/2) + Θ(n); group size is irrelevant to the final complexity", "T(n) &le; T(n/2) + T(n/2) + Θ(n log n); group size 5 minimizes the log factor specifically", "T(n) &le; T(n&minus;5) + Θ(n); group size 5 guarantees removing exactly 5 elements per call"],
"ans": 0,
"exp": "Median-of-medians recursively finds the median of ~n/5 group-medians (cost T(n/5)), uses it as a pivot, and recurses into the larger partition side, which is provably at most 7n/10 elements (cost T(7n/10)), plus Θ(n) for grouping/partitioning. Since 1/5 + 7/10 = 9/10 &lt; 1, the recurrence solves to Θ(n) via the substitution method (this specific fractional sum being strictly less than 1 is what makes the linear bound provable — smaller groups like 3 would fail this inequality). (B) discards the crucial group-size-driven fractional split, misrepresenting the whole point of the algorithm. (C) fabricates an incorrect recurrence shape and an irrelevant justification about a 'log factor' — there's no log factor to minimize here since the final answer is linear. (D) drastically misunderstands the algorithm's reduction; it doesn't remove a constant number of elements per call, it removes a constant fraction."
})

Q.append({
"q": "Why does choosing groups of 3 (instead of 5) in the median-of-medians algorithm fail to guarantee linear worst-case time?",
"opts": ["With groups of 3, the guaranteed fraction of eliminated elements leads to a recurrence like T(n) &le; T(n/3) + T(2n/3) + Θ(n), where the fractions sum to exactly 1, causing the recurrence to solve to Θ(n log n) instead of Θ(n)", "Groups of 3 cause the algorithm to be incorrect, not just slower", "Groups of 3 make the partitioning step take Θ(n&sup2;) time directly", "There is no difference; groups of 3 also yield Θ(n)"],
"ans": 0,
"exp": "With groups of 3, only about half of the group-medians are provably less than the pivot (roughly n/6 elements guaranteed on each side from full groups), leading to a worst-case recursion where the larger partition can be as large as roughly 2n/3, giving T(n) &le; T(n/3) + T(2n/3) + Θ(n). Here the fractions n/3 and 2n/3 sum to exactly n (i.e., the coefficients sum to 1), which is precisely the boundary case where the substitution method's inductive proof fails to produce a strictly decreasing bound, and the recurrence instead solves to Θ(n log n), not Θ(n) — this is why groups of 5 (giving 1/5+7/10=9/10&lt;1) were specifically chosen. (B) is false; groups of 3 still work correctly, just less efficiently in the worst case. (C) is a fabricated and unrelated claim; the partitioning step itself is unaffected and remains Θ(n). (D) is factually incorrect and misses the entire mathematical point of why 5 was chosen over smaller odd numbers."
})

Q.append({
"q": "Consider the D&C algorithm for computing x&#8319; (integer exponentiation) via: if n is even, x&#8319; = (x<sup>n/2</sup>)&sup2;; if odd, x&#8319; = x&middot;(x<sup>(n&minus;1)/2</sup>)&sup2;. What is its time complexity, and what is the key advantage over the naive Θ(n) iterative multiplication approach?",
"opts": ["Θ(log n), because the exponent is halved at each recursive step regardless of parity", "Θ(n), identical to the naive approach since squaring still requires n multiplications total", "Θ(n log n), because each squaring operation itself costs Θ(log n)", "Θ(&radic;n), by analogy to other 'fast' algorithms"],
"ans": 0,
"exp": "This is 'fast exponentiation' (exponentiation by squaring): the recurrence is T(n) = T(n/2) + Θ(1) regardless of whether n is even or odd (the odd case just adds one extra constant-time multiplication), which solves to Θ(log n) by Master theorem Case 2 (a=1, b=2, f(n)=Θ(1)=n&#8304;). This is a dramatic improvement over the naive Θ(n) approach of multiplying x by itself n&minus;1 times. (B) describes the naive approach's complexity, missing the entire point of why the recursive halving strategy is introduced. (C) incorrectly assumes each multiplication itself costs Θ(log n) in this model — at this level of the course, multiplication of numbers (not matrices) is standardly treated as Θ(1) per operation, and even accounting for bit-complexity, that's not the intended justification here. (D) is a fabricated complexity with no derivation basis in this recurrence."
})

with open("/home/claude/mcq/dc_part_a.json", "w") as f:
    import json
    json.dump(Q, f)
print(len(Q))
