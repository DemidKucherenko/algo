template <class T>
class FenwickTree {
public:
    inline int f(int i)
    {
        return i & (i + 1);
    }

    inline int fup(int i)
    {
        return min(i + 1 + (i - f(i)), (int)n);
    }

    inline int h(int i)
    {
        return i | (i + 1);
    }

    explicit FenwickTree(const vector<T>& array, function<T(T, T)> func, T neutral) : forw(array.size(), neutral), back(array.size(), neutral), func(func), neutral(neutral), n(array.size())
    {
        for (int i = 0; i < array.size(); i++)
        {
            modify(i, array[i]);
        }
    }

    T getFunc(int left, int right)
    {
        T res = neutral;
        while (right >= 0 && f(right) >= left)
        {
            res = func(res, forw[right]);
            right = f(right) - 1;
        }
        while (right >= left && h(left - 1) <= right)
        {
            res = func(res, back[left - 1]);
            left = h(left - 1) + 1;
        }
        assert(left == right + 1);
        return res;
    }

    void modify(int i, T val)
    {
        int j = i - 1;
        T down = neutral;
        while (j >= f(i))
        {
            down = func(down, forw[j]);
            j = f(j) - 1;
        }
        forw[i] = func(down, val);
        int k = h(i);
        T up = back[i];
        while (k < forw.size())
        {
            while (f(k) <= j)
            {
                down = func(down, forw[j]);
                j = f(j) - 1;
            }
            forw[k] = func(func(down, up), val);
            up = func(up, back[k]);
            k = h(k);
        }

        j = i - 1;
        up = back[i];
        k = i;
        down = neutral;
        while (j >= 0)
        {
            if (f(j) == j)
            {
                assert(j == i - 1);
                back[j] = val;
                down = func(down, forw[j]);
                j = f(j) - 1;
                continue;
            }
            while (fup(j) > fup(k))
            {
                k = fup(k);
                up = func(up, back[k]);
            }
            if (fup(j) > i) {
                assert(fup(j) == fup(k));
                back[j] = func(func(up, val), down);
            } else {
                back[j] = func(val, down);
            }
            down = func(down, forw[j]);
            j = f(j) - 1;
        }
    }

    void print()
    {
        for (int x : forw)
        {
            err << x << " ";
        }
        err << endl;
        for (int x : back)
        {
            err << x << " ";
        }
        err << endl;
    }

private:
    vector<T> forw;
    vector<T> back;
    function<T(T, T)> func;
    T neutral;
    size_t n;
};
