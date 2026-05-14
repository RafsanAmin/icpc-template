using namespace std;
template <class T, class = void> struct is_iterable : false_type {};
template <class T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>>
    : true_type {};
template <class T, class = void> struct is_streamable : false_type {};
template <class T> struct is_streamable<T, void_t<decltype(cerr << declval<T>())>> : true_type {};
template <class T> void dbg_print(const T &x);
template <class A, class B> void dbg_print(const pair<A, B> &p) {
  cerr << "{"; dbg_print(p.first); cerr << ", "; dbg_print(p.second); cerr << "}";
}

template <class T> void dbg_print(const T &x) {
  if constexpr (is_streamable<T>::value) {
    cerr << x;
  } else if constexpr (is_iterable<T>::value) {
    cerr << "{"; int f = 0;
    for (auto &i : x) {
      if (f++) cerr << ", "; dbg_print(i);
    } cerr << "}";
  } else { cerr << "<unprintable>"; }
}
void dbg_out() { cerr << RESET << "]\n"; }

template <class T, class... V> void dbg_out(T t, V... v) {
  dbg_print(t);if (sizeof...(v)) cerr << ", ";dbg_out(v...);
}

template <class T> void dbg_array(const T *a, int n) {
  cerr << "{";
  for (int i = 0; i < n; i++) {
    if (i) cerr << ", "; cerr << a[i];
  }
  cerr << "}";
}

#ifdef DEBUG
#else
#define debug(...)
#define dbg_arr(...)
#endif
