<p><div align = "center"> <h1>2019-2 알고리즘 설계와 분석(CSE3081) MP1 보고서<h1>
  <h2>학번 : 20150038 학과 : 철학과 이름 : 김재원<h2></div></p>

<p><h3>- Experiment environment : </h3>
O/S : Window10 <br>
CPU : Intel(R) Core(TM) i5-8265U CPU @ 1.60GHz 1.80GHz<br>
RAM : 8.00GB<br>
System : 64bit O/S , x64 based processor<br></p>

<p><h3>- Experiment setup : <h3> 
Input range : -10 ~ 10 (All have same Range)
행과 열의 수는 아래 표에 제시했다. 측정의 용이성을 위해 행과 열의 수는 5의 배수로 설정했고 50을 넘어가면 알고리즘 간 복잡도 차이가 충분히 크고 O(N^6) 알고리즘의 수행 시간이 너무 길기 때문에 5 ~ 50까지 10회에 걸쳐 실험을 수행했다. 추가로 input size가 두 배씩 늘어날 때 알고리즘 수행 시간에 일어나는 변화를 확인하기위해 80 x 80 matrix도 확인했고 그 결과를 아래에 기재했다. 각 알고리즘을 수행하는 시간의 단위는 miliseconds이다. </p>

<h3> - Your comments on the experience : </h3>
<table>
  <tr>
    <th>   </th>
    <th>Row</th>
    <th>Col</th>
    <th>Time(ms)</th>
  </tr>
  <tr>
    <td>O(N^6)</td>
    <td>5</td>
    <td>5</td>
    <td>10</td>
  </tr>
  <tr>
    <td>O(N^4)</td>
    <td>5</td>
    <td>5</td>
    <td>8</td>
  </tr> 
  <tr>
    <td>O(N^3)</td>
    <td>5</td>
    <td>5</td>
    <td>4</td>
  </tr>
</table><br>

<table>
  <tr>
    <th>   </th>
    <th>Row</th>
    <th>Col</th>
    <th>Time(ms)</th>
    <th>difference</th>
  </tr>
  <tr>
    <td>O(N^6)</td>
    <td>10</td>
    <td>10</td>
    <td>395</td>
    <td>39.5</td>
  </tr>
  <tr>
    <td>O(N^4)</td>
    <td>10</td>
    <td>10</td>
    <td>35</td>
    <td>4.4</td>
  </tr> 
  <tr>
    <td>O(N^3)</td>
    <td>10</td>
    <td>10</td>
    <td>23</td>
    <td>5.8</td>
  </tr>
</table><br>

<table>
  <tr>
    <th>   </th>
    <th>Row</th>
    <th>Col</th>
    <th>Time(ms)</th>
    <th>difference</th>
  </tr>
  <tr>
    <td>O(N^6)</td>
    <td>20</td>
    <td>20</td>
    <td>15.113</td>
    <td>77.1</td>
  </tr>
  <tr>
    <td>O(N^4)</td>
    <td>20</td>
    <td>20</td>
    <td>0.453</td>
    <td>12.6</td>
  </tr> 
  <tr>
    <td>O(N^3)</td>
    <td>20</td>
    <td>20</td>
    <td>0.129</td>
    <td>9.2</td>
  </tr>
</table><br>

이번 과제의 목적은 추상적인 이론으로 학습한 시간 복잡도 개념을 실제 프로그램을 통해 경험적으로 확인하고 깊이 이해하는 것이다. 이를 위해 input size를 다르게 하여 반복적으로 실험을 했고 그 결과를 기록했다.
input size가 작을 때는 알고리즘 간 수행 시간의 차이가 크지 않았지만 input size가 커지면서 각 알고리즘에 소요된 수행 시간의 격차가 큰 차이로 벌어졌다. O(N^6)의 알고리즘의 수행시간은 기하급수적으로 증가해서 Row와 Col이 50이 되자 O(N^4)와 O(N^3)과 한 그래프에 표현하기 힘들 정도로 큰 차이를 보였다. 
초기에 O(N^4)와 O(N^3)은 차이가 많이 나지 않았지만 Row와 Col이 커지면서 큰 차이가 나게 됐다. 물론 O(N^6)과 비교하면 큰 차이가 아니지만 Row와 Col이 더욱 커지면 큰 차이가 날 것으로 예상된다. 이 실험을 통해서 input size가 충분히 커지면 복잡도 사이의 작은 차이는 무시할 수 있다는 것을 알 수 있다. 
과제를 진행하면서 의아한 점은 다음과 같다. Input size가 2배로 증가할 때 O(N^6) 알고리즘의 수행시간은 대략 2^6 = 64배 증가할 것으로 예상했다. 마찬가지로 O(N^4) 알고리즘은 약 16배, O(N^3) 알고리즘의 수행시간은 약 8배 증가한다고 예상했다. 전체적으로 그런 추세를 보이는 것 같지만 배수 차이가 역전되는 지점이 있어서 의아했다.


