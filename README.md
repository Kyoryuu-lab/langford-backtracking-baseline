<h1>langford-backtracking-baseline</h1>
<p>Langford Sequences L(2, n): Sequential Backtracking Baseline</p>

<h2>Project description</h2>
<p>This project introduces recursive problem solving and backtracking for combinatorial sequence generation:</p>
<ol>
  <li>
    <dl>
      <dt>Langford sequence problem definition L(2, n):</dt>
      <dd>Arranges numbers <code>1, 1, 2, 2, ..., n, n</code> into a sequence of length <code>2n</code> such that exactly <code>k</code> numbers exist between the two occurrences of number <code>k</code>.</dd>
    </dl>
  </li>
  <li>Implements depth-first search (DFS) with recursive state placement and backtracking.</li>
  <li>Serves as the deterministic ground truth and timing baseline ($T_{\text{seq}}$) for subsequent parallel tasks.</li>
  <li>Evaluates performance for sequences up to <code>n = 11</code> and <code>n = 12</code>.</li>
</ol>

<h2>Project files</h2>
<table>
  <tr>
    <th colspan="2">langford-backtracking-baseline</th>
  </tr>
  <tr>
    <td>CMakeLists.txt</td>
    <td>Standard C++20 CMake configuration</td>
  </tr>
  <tr>
    <td>main.cpp</td>
    <td>Recursive sequential Langford sequence solver and solution counter</td>
  </tr>
  <tr>
    <td>README.md</td>
    <td>Project documentation and combinatorial constraints</td>
  </tr>
</table>

<h2>Installation and launch</h2>
<ol>
  <b>
    <li>
      <dl>
        <dt>Clone repository</dt>
        <dd>
          <code>git clone https://github.com/Kyoryuu-lab/langford-backtracking-baseline.git</code>
        </dd>
        <dd>
          <code>cd langford-backtracking-baseline</code>
        </dd>
      </dl>
    </li>
  </b>
  <b>
    <li>
      <dl>
        <dt>Compile project</dt>
        <dd>
          <code>cmake -B build -DCMAKE_BUILD_TYPE=Release</code>
        </dd>
        <dd>
          <code>cmake --build build --config Release</code>
        </dd>
      </dl>
    </li>
  </b>
  <b>
    <li>
      <dl>
        <dt>Run sequential program</dt>
        <dd>
          <code>./build/main</code>
        </dd>
      </dl>
    </li>
  </b>
</ol>

<h2>Example of console output</h2>
<samp>
  <p>
    ====================================================<br />
    PVA Aufgabe 4.1: Langford Sequential Baseline<br />
    Testing for n = 11 (Board length: 22)<br />
    ====================================================<br />
    Searching all valid permutations...<br />
    Found: 355840 solutions.<br />
    Execution time: 840.52 ms<br />
    Status: COMPLETED (Baseline established)<br />
    ====================================================
  </p>
</samp>
