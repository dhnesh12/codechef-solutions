#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

const double eps = 1e-8;

template <class T>
struct Matrix
{
  static Matrix<T> getNormal(int R) {
    Matrix<T> ret(R,R);
    for (int i = 0; i < R; ++i)
      ret.data[i][i] = 1;
    return ret;
  }

  int R, C;
  vector<vector<T> > data;

  Matrix(int r,int c) 
  {
    R = r;
    C = c;
    data = vector<vector<T> >(R, vector<T>(C, 0));
  }

  Matrix(const Matrix & x) 
  {
    R = x.R;
    C = x.C;
    data = x.data;
  }

  /** swap two row in this matrix */
  void swapRow(int r1, int r2)
  {
    if (r1 == r2 || r1 >= R || r2 >= R) return;
    for (int j = 0; j < C; ++j)
      swap(data[r1][j], data[r2][j]);
  }

  /** swap two column in this matrix */
  void swapCol(int c1, int c2)
  {
    if (c1 == c2 || c1 >= C || c2 >= C) return;
    for (int i = 0; i < R; ++i)
      swap(data[i][c1], data[i][c2]);
  }

  /** subtract row2 = row2 - k * row1 */
  void subtractRowIFromRowJ(int r1, int r2, T k)
  {
    if (r1 == r2 || r1 >= R || r2 >= R) return;
    for (int j = 0; j < C; ++j)
    {
      data[r2][j] -= data[r1][j];
      if (data[r2][j] < 0)
        data[r2][j] = 1;
    }
  }

  bool isZero()
  {
    for (int i = 0; i < R; ++i)
      for (int j = 0; j < C; ++j)
        if (data[i][j] > 0)
          return false;
    return true;
  }

  bool isZeroRow(int r)
  {
    for (int j = 0; j < C; ++j)
      if (data[r][j] > 0)
        return false;
    return true;
  }

  /** merge this matrix with matrix right */
  Matrix<T> rightMergeMatrix(Matrix<T> & right)
  {
    if (right.R != R) 
      return (*this);

    Matrix<T> newMatrix(R, C + right.C);
    for (int i = 0; i < R; ++i)
      for (int j = 0; j < newMatrix.C; ++j)
        if (j < C)
          newMatrix.data[i][j] = data[i][j];
        else
          newMatrix.data[i][j] = right.data[i][j - C];
    return newMatrix;
  }

  /** do Gaussian Elimination on this matrix 
   * As explained above, Gaussian elimination writes a given m × n matrix A 
   * uniquely as a product of an invertible m × m matrix S and a row-echelon matrix T. 
   * Here, S is the product of the matrices corresponding to the row operations performed.
   * The formal algorithm to compute T from A follows. We write A[i,j] for the entry in row i, column j in matrix A. 
   * The transformation is performed in place, 
   * meaning that the original matrix A is lost and successively replaced by T.
   * @side effect matrix will change 
   */
  void gaussianElimination()
  {
    int i = 0;
    int j = 0;
    while (i < R && j < C)
    {
      int maxi = i;
      for (int k = i; k < R; ++k)
        if (data[k][j] > 0)
        {
          maxi = k;
          break;
        }

      if (data[maxi][j] > 0)
      {
        /** swap rows i and maxi, but do not change the value of i 
         * Now A[i,j] will contain the old value of A[maxi,j]. 
         * divide each entry in row i by A[i,j] 
         * Now A[i,j] will have the value 1.  
         */
        swapRow(i, maxi);

        /** subtract A[u,j] * row i from row u 
         * Now A[u,j] will be 0, since A[u,j] - A[i,j] * A[u,j] = A[u,j] - 1 * A[u,j] = 0.
         */
        for (int u = i + 1; u < R; ++u)
        {
          if (data[u][j] > 0)
            subtractRowIFromRowJ(i, u, data[u][j]);
        }
                 
        i++;
      }
      j++;
    }
  }

  /** Return the rank of this matrix 
   * @side effect the matrix will change
   */
  int rank()
  {
    gaussianElimination();
    int ret = 0;
    for (int i = 0; i < R; ++i)
      if (!isZeroRow(i))
        ret++;
    return ret;
  }
};

  template <class T>
ostream & operator << (ostream & out , const Matrix<T> & a)
{
  for (int i = 0; i < a.R; ++i) {
    for (int j = 0; j < a.C; ++j)
      out << setprecision(3) << a.data[i][j] << "\t";
    out << endl;
  }
  return out;
}

  template <class T>
Matrix<T> operator + (const Matrix<T> & a , const Matrix<T> & b)
{
  assert(a.R == b.R);
  assert(a.C == b.C);

  Matrix<T> ret(a.R , a.C);
  for (int i = 0; i < ret.R; ++i)
    for (int j = 0; j < ret.C; ++j)
      ret.data[i][j] = a.data[i][j] + b.data[i][j];
  return ret;
}

  template <class T>
Matrix<T> operator - (const Matrix<T> & a , const Matrix<T> & b)
{
  assert(a.R == b.R);
  assert(a.C == b.C);

  Matrix<T> ret(a.R , a.C);
  for (int i = 0; i < ret.R; ++i)
    for (int j = 0; j < ret.C; ++j)
      ret.data[i][j] = a.data[i][j] - b.data[i][j];
  return ret;
}

  template <class T>
Matrix<T> operator * (const Matrix<T> & a , double x)
{
  Matrix<T> ret(a.R , a.C);
  for (int i = 0; i < ret.R; ++i)
    for (int j = 0; j < ret.C; ++j)
      ret.data[i][j] = a.data[i][j] * x;
  return ret;
}

  template <class T>
Matrix<T> operator * (const Matrix<T> & a , const Matrix<T> & b)
{
  assert(a.C == b.R);
  Matrix<T> ret(a.R , b.C);

  for (int i = 0; i < a.R; ++i)
    for (int j = 0; j < b.C; ++j)
      for (int k = 0; k < a.C; ++k)
        ret.data[i][j] += a.data[i][k] * b.data[k][j];
  return ret;
}

  template <class T>
Matrix<T> operator ^ (const Matrix<T> & a , int deg)
{
  if (deg == 0)
    return Matrix<T>::getNormal(a.R);
  if (deg == 1) 
    return a;

  int half = deg / 2;
  int remain = deg - half * 2;
  Matrix<T> tmp = a ^ half;
  if (remain) 
    return tmp * tmp * a;
  else
    return tmp * tmp;
}

/** 
 * Return the inverse of this matrix
 */
template <class T>
bool inverseMatrix(Matrix<T> & a)
{
  vector<int> is(a.R, 0);
  vector<int> js(a.R, 0);
  T t;
  if (a.R != a.C) 
    return false;

  for (int k = 0; k < a.R; k++) 
  {
    t = 0;
    for (int i = k; i < a.R; i++)
      for (int j = k; j < a.R; j++)
        if (fabs(a.data[i][j]) > t)
          t = fabs(a.data[is[k] = i][js[k] = j]);

    if (fabs(t) < eps) return false;

    if (is[k] != k) a.swapRow(k, is[k]);
    if (js[k] != k) a.swapCol(k, js[k]);

    a.data[k][k] = 1 / a.data[k][k];
    for (int j = 0; j < a.R; j++)
      if (j != k) a.data[k][j] *= a.data[k][k];

    for (int i = 0; i < a.R; i++) if (i != k)
      for (int j = 0; j < a.R; j++) if (j != k)
        a.data[i][j] -= a.data[i][k] * a.data[k][j];

    for (int i = 0; i < a.R; i++)
      if (i != k) a.data[i][k] *= -a.data[k][k];
  }

  for (int k = a.R - 1; k >= 0; k--){
    for (int j = 0; j < a.R; j++)
      if (js[k] != k)
        t = a.data[k][j], a.data[k][j] = a.data[js[k]][j], a.data[js[k]][j] = t;
    for (int i = 0; i < a.R; i++)
      if (is[k] != k)
        t = a.data[i][k], a.data[i][k] = a.data[i][is[k]], a.data[i][is[k]] = t;
  }
  return true;
}

/** Solve linear equation
 * A m * n matrix 
 * b m * 1 vector
 * @return n * 1 solution
 */
template <class T>
Matrix<T> solveEquation(Matrix<T> & A, Matrix<T> & b, int & solutions)
{
  Matrix<T> nA = A;
  Matrix<T> zA = A.rightMergeMatrix(b);
  Matrix<T> ret(A.C, 1);

  int rank1 = nA.rank();
  int rank2 = zA.rank();
  //cout << nA << endl;
  //cout << zA << endl;

  //cout << rank1 << "\t" << rank2 << endl;

  if (rank1 != rank2)
  {
    solutions = 0;
    return ret;
  }

  if (rank1 < A.R)
    solutions = 2;
  else
    solutions = 1;


  /** cal the solution */
  for (int i = zA.R - 1; i >= 0; --i)
  {
    if (zA.isZeroRow(i)) continue;
    T nowB = zA.data[i][zA.C - 1];
    for (int j = 0; j < zA.C - 1; ++j)
      if (fabs(zA.data[i][j]) > 0)
      {
        ret.data[j][0] = nowB / zA.data[i][j];
        break;
      }
  }
  
  return ret;
}

/**
double det(const mat& a){
  int i,j,k,sign=0;
  double b[MAXN][MAXN],ret=1,t;
  if (a.n!=a.m)
    return 0;
  for (i=0;i<a.n;i++)
    for (j=0;j<a.m;j++)
      b[i][j]=a.data[i][j];
  for (i=0;i<a.n;i++){
    if (zero(b[i][i])){
      for (j=i+1;j<a.n;j++)
        if (!zero(b[j][i]))
          break;
      if (j==a.n)
        return 0;
      for (k=i;k<a.n;k++)
        t=b[i][k],b[i][k]=b[j][k],b[j][k]=t;
      sign++;
    }
    ret*=b[i][i];
    for (k=i+1;k<a.n;k++)
      b[i][k]/=b[i][i];
    for (j=i+1;j<a.n;j++)
      for (k=i+1;k<a.n;k++)
        b[j][k]-=b[j][i]*b[i][k];
  }
  if (sign&1)
    ret=-ret;
  return ret;
}
*/

int N;
int M;
int ori[300][300];
int temp[300][300];

map<pair<int, int>, int> specialLight;

void getFinalRow(vector<int> & finalRow, vector<int> & buttonOn)
{
  finalRow = vector<int>(N, 0);
  buttonOn = vector<int>(M, 0);

  for (int i = 0; i < N - 1; ++i)
    for (int j = 0; j < N; ++j)
      if (temp[i][j] == 1)
      {
        temp[i][j] = 0;
        temp[i + 1][j] = 1 - temp[i + 1][j];
        if (j > 0)
          temp[i + 1][j - 1] = 1 - temp[i + 1][j - 1];
        if (j < N - 1)
          temp[i + 1][j + 1] = 1 - temp[i + 1][j + 1];
        if (i + 2 < N)
          temp[i + 2][j] = 1 - temp[i + 2][j];

        pair<int, int> light = make_pair(i + 1, j);
        if (specialLight.find(light) != specialLight.end())
        {
          buttonOn[specialLight[light]] = 1;
        }
      }

  for (int i = 0; i < N; ++i)
    finalRow[i] = temp[N - 1][i];
}

void clear()
{
  specialLight.clear();
}

void deal()
{
  scanf("%d%d", &N, &M);

  string line;
  getline(cin, line);
  for (int i = 0; i < N; ++i)
  {
    getline(cin, line);
    for (int j = 0; j < N; ++j)
      ori[i][j] = line[j] - '0';
  }

  for (int i = 0; i < M; ++i)
  {
    int row = 0, col = 0;
    scanf("%d%d", &row, &col);
    specialLight[make_pair(row - 1, col - 1)] = i;
  }

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      temp[i][j] = ori[i][j];


  vector<int> finalRow;
  vector<int> buttonOn;
  getFinalRow(finalRow, buttonOn);
  Matrix<int> B(N + M, 1);
  for (int i = 0; i < finalRow.size(); ++i)
    B.data[i][0] = finalRow[i];
  for (int i = 0; i < buttonOn.size(); ++i)
    B.data[i + N][0] = buttonOn[i];


  Matrix<int> A(N + M, N);
  for (int k = 0; k < N; ++k)
  {
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        temp[i][j] = 0;

    for (int j = 0; j < N; ++j)
        temp[0][j] = 0;
    temp[0][k] = 1;
    temp[1][k] = 1;
    if (k > 0)
      temp[0][k - 1] = 1;
    if (k < N - 1)
      temp[0][k + 1] = 1;


    getFinalRow(finalRow, buttonOn);

    for (int i = 0; i < finalRow.size(); ++i)
      A.data[i][k] = finalRow[i];
    for (int i = 0; i < buttonOn.size(); ++i)
      A.data[i + N][k] = buttonOn[i];
  }

  Matrix<int> C = A.rightMergeMatrix(B);
  
  //int rankA = A.rank();
  int rankC = C.rank();

  bool ans = true;
  for (int i = 0; i < C.R; ++i)
  {
    bool empty = true;
    for (int j = 0; j < C.C - 1; ++j)
      if (C.data[i][j] > 0)
      {
        empty = false;
        break; 
      }
    if (empty && C.data[i][C.C - 1] > 0)
      ans = false;
  }

  if (ans)
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T--)
  {
    clear();
    deal();
  }

  return 0;
}
