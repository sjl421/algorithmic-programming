 
//Shreyans Sheth [bholagabbar]
 
#include <bits/stdc++.h>
using namespace std;
#define readFile freopen("E:/Shreyans/Documents/Coding Workspace/STDINPUT.txt","r",stdin);
#define getPrecision(s,p) fixed<<setprecision(p)<<s
#define boostIO ios_base::sync_with_stdio(0), cin.tie(0)
#define CLR(s) memset(&s, 0, sizeof s)
#define hashset unordered_set    //JAVA Feels :')
#define hashmap unordered_map
#define pb push_back
#define mp make_pair
#define sz 100001
#define F first
#define S second
#define endl '\n'
 
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
class dynamicConvexHullTrick {
private:
    struct Line {
        ll a;
        ll b;
        ll val;
        double xLeft;
        bool type;
        Line(ll a = 0 , ll b = 0) {
            this -> a = a;
            this -> b = b;
            xLeft = -1e18;
            type = 0;
            val = 0;
        }
        ll valueAt(ll x) const {
            return 1LL * a * x + b;
        }
        friend bool areParallel(const Line &l1, const Line &l2) {
            return l1.a == l2.a;
        }
        friend double intersectX(const Line &l1 , const Line &l2) {
            return areParallel(l1 , l2) ? 1e18 : 1.0 * (l2.b - l1.b) / (l1.a - l2.a);
        }
        bool operator < (const Line &l2) const {
            if(!l2.type)
                return a < l2.a;
            return xLeft > l2.val;
        }
    };
 
    set<Line> hull;
 
    bool hasPrev(set<Line> :: iterator it) {
        return it != hull.begin();
    }
    
    bool hasNext(set<Line> :: iterator it) {
        return it != hull.end() && next(it) != hull.end();
    }
    
    bool irrelevant(const Line &l1 , const Line &l2 , const Line &l3) {
        return intersectX(l1,l3) <= intersectX(l1,l2);
    }
    
    bool irrelevant(set<Line> :: iterator it) {
        return hasPrev(it) && hasNext(it) && (irrelevant(*next(it) , *it , *prev(it)));
    }
 
    set<Line> :: iterator updateLeftBorder(set<Line> :: iterator it) {
        if(!hasNext(it)) {
            return it;
        }
        double val = intersectX(*it , *next(it));
        Line buf(*it);
        it = hull.erase(it);
        buf.xLeft = val;
        it = hull.insert(it, buf);
        return it;
    }
 
public:
    void addLine(ll a , ll b) {
        Line l3 = Line(a, b);
        set<Line> :: iterator it = hull.lower_bound(l3);
        if(it != hull.end() && areParallel(*it , l3)) {
            if(it -> b > b) {
                it = hull.erase(it);
            }
            else {
                return;
            }
        }
        it = hull.insert(it, l3);
        if(irrelevant(it)) {
            hull.erase(it);
            return;
        }
        while(hasPrev(it) && irrelevant(prev(it))) {
            hull.erase(prev(it));
        }
        while(hasNext(it) && irrelevant(next(it))) {
            hull.erase(next(it));
        }
        it = updateLeftBorder(it);
        if(hasPrev(it)) {
            updateLeftBorder(prev(it));
        }
        if(hasNext(it)) {
            updateLeftBorder(next(it));
        }
    }
 
    ll getBest(ll x) {
        Line q;
        q.val = x;
        q.type = 1;
        auto bestLine = hull.lower_bound(q);
        if(bestLine == hull.end()) {
            return 1e18;
        }
        return bestLine -> valueAt(x);
    }
};
 
struct Cyclist {
    ll pos, prevTime, prevSpeed;
};
 
Cyclist id[50001];
dynamicConvexHullTrick cht;
 
void initializeCyclist(int i) {
    cht.addLine(0, 0);
    id[i].pos = 0;
    id[i].prevTime = 0;
    id[i].prevSpeed = 0;
}
 
void update(int i, ll currTime, ll newSpeed) {
    id[i].pos += (currTime - id[i].prevTime) * id[i].prevSpeed;
    id[i].prevSpeed = newSpeed;
    id[i].prevTime = currTime;
    /*
    If position of a person is xx and speed is vv, then at time tt, his position will be x+v*tx+v*t.
    Now, assume that we change its speed at time TT from vv to v′v′.
    Now position of the person at time t>Tt>T, will be
    x+v*T+v′*(t−T)
    =(x+(v−v′)*T)+v′*t i.e. x′+v′t
    where x′=(x+(v−v′)*T)x′=(x+(v−v′)*T).

    refer editorial: https://discuss.codechef.com/questions/78425/cyclrace-editorial
    */
    //Since implementation finds lower hull, we insert reversed lines (y = -m*X -c where X = time here)
    cht.addLine(-newSpeed, -(id[i].pos - newSpeed*currTime));
}
 
ll query(ll currTime) {
    return -cht.getBest(currTime);
}
 
int main()
{
    boostIO;
    int n, q, type;
    ll ntime, newSpeed, cyclistId;
    cin >> n >> q;
    for (int i = 1; i <= n; i++){
        initializeCyclist(i);
    }
    while (q--) {
        cin >> type >> ntime;
        if (type == 1) {
            cin >> cyclistId >> newSpeed;
            update(cyclistId, ntime, newSpeed);
        } else {
            cout << query(ntime) <<endl;
        }
    }
    return 0;
}