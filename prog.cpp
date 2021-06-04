#include <bits/stdc++.h>

using namespace std;

int n,m;
/**
 * @brief
 * n
 *  => MapSize
 * m
 *  => QueryNum
 */
int dy[4]={1,0,-1,0};
int dx[4]={0,1,0,-1};
vector<vector<bool>> check(250,vector<bool>(250,false));
/**
 * @brief
 * 移動先が既に到達した範囲か、到達していない範囲かを判断するための配列
 */
vector<vector<char>> ma(250,vector<char>(250,' '));
/**
 * @brief
 * mapの状況を把握
 */
vector<string> s(2000);
/**
 * @brief
 * 命令を格納しておく
 * 命令の上限は2000個だから、それが全て入るだけ確保しておく。
 *
 */
vector<int> sn(2000,0);
/**
 * @brief
 * 命令が含む移動量を数字として確保しておく。
 *
 */
vector<vector<pair<int,int>>> sr(2000, vector<pair<int,int>>(0));
/**
 * @brief
 *
 * 移動量を累積的に表現するための配列
 *
 */

void dfs(int y,int x);
void sdfs(int y,int x);
signed main(){
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin>>n; // マップサイズを入力
    vector<int> y(n),x(n); // 障害物の位置を別別の配列で管理
    for(int i=0;i<n;i++){ // 障害物の座標を入力
        cin>>y[i]>>x[i];
        y[i]--;
        x[i]--;
        ma[y[i]][x[i]]='#';
    }
    cin>>m; // 組み合わされた移動命令を入力
    for(int i=0;i<m;i++){
        cin>>s[i]; // 移動命令を文字列として入力
        sn[i]=s[i].size();
        int ry=0,rx=0;
        for(int j=0;j<s[i].size();j++){ // 命令分を値に組み換え
            if(s[i][j]=='U'){
                ry--;
            }else if(s[i][j]=='D'){
                ry++;
            }else if(s[i][j]=='L'){
                rx--;
            }else if(s[i][j]=='R'){
                rx++;
            }
            sr[i].push_back(make_pair(ry,rx));
        }
    }
    for(int i=0;i<m;i++){ // 移動の累積を出力。
        for(int j=0;j<sn[i];j++){
            cout<<sr[i][j].first<<' '<<sr[i][j].second<<'\n';

            // <<!>> test_output
            cout << "<<!>>\n" << endl;
            // ----------------
        }

        cout<<'\n';
    }
    //命令の圧縮
    dfs(0,0);
    sdfs(0,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(check[i][j]==true){
                cout<<"NO\n";
                return 0;
            }
        }
    }
    cout<<"YES\n";
    cout<<m<<'\n';
    cout<<1;
    for(int i=2;i<=m;i++){
        cout<<' '<<i;
    }
    cout<<'\n';
    return 0;
}

/**
 * @brief
 *
 * @param y
 * @param x
 */
void dfs(int y,int x){
    check[y][x]=true;
    for(int i=0;i<4;i++){
        int ny=y+dy[i],nx=x+dx[i];
        if(0<=ny&&ny<n&&0<=nx&&nx<n&&check[ny][nx]==false&&ma[ny][nx]!='#'){
            dfs(ny,nx);
        }
    }
    return;
}

/**
 * @brief
 *
 * @param y
 * @param x
 */
void sdfs(int y,int x){
    check[y][x]=false;
    for(int i=0;i<m;i++){
        int j,ny,nx;
        for(j=0;j<sn[i];j++){
            ny=y;
            nx=x;
            ny+=sr[i][j].first;
            nx+=sr[i][j].second;
            if(ny<0||n<=ny||nx<0||n<=nx||ma[ny][nx]=='#'){
                break;
            }
        }
        ny=y+sr[i][sn[i]-1].first;
        nx=x+sr[i][sn[i]-1].second;
        if(j==s[i].size()&&0<=ny&&ny<n&&0<=nx&&nx<n&&check[ny][nx]==true){
            sdfs(ny,nx);
        }
    }
    return;
}