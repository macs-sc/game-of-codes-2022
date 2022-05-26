
//
// Created by egor http://github.com/chermehdi/egor
// 
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

const string kSentinal = "None";

// To answer this problem, you can simply come up with the JSON grammar
// and created a simple recursive descent parser (based on the constraints of the problem)
// that keeps track of the paths and records values as they come down.
//
// Proposed JSON Grammar:
//
// value: {obj} | [arr] | pri
// obj: {} | { members } 
// members: member | member, members
// member:  "\w": value
// arr: [] | [ elements ]
// elements: value | value, elements

int value(const string& s, int at);
vector<string> parts;
unordered_map<string, string> paths;

void expect(char expected, char got) {
  if(expected != got) {
    
    exit(-1);
  }
}

pair<int, int> read_int(const string& s, int at) {
  int n = s.length();
  int res = 0;
  while(at < n && isdigit(s[at])) {
    res = res * 10 + (s[at] - '0');
    ++at;
  }
  return {res, at};
}

// reads a quoted string, expectes the first character 
// to be the first double quote string.
// returns the index after the last quote in the string.
pair<string, int> read_str(const string& s, int at) {
  expect('"', s[at]);
  int n = s.length();
  ++at;
  string res = "";
  while(at < n && s[at] != '"') {
    res += s[at];
    ++at;
  }
  return {res, at + 1};
}

string get_path(vector<string>& path) {
  string ans = "$";
  for(int i = 0; i < path.size(); i++) {
    ans += ".";
    ans += path[i];
  }
  return ans;
}

int member(const string& s, int at) {
  int c = s[at];
  expect('"', c);
  auto res = read_str(s, at);
  parts.push_back(res.first);
  at = res.second;
  expect(':', s[at]);
  ++at;
  int end = value(s, at);
  auto path = get_path(parts);
  
  if(paths.count(path)) {
    paths[path] = s.substr(at, end - at);
  }
  return end;
}

int members(const string& s, int at) {
  int end = member(s, at);
  parts.pop_back();
  if(s[end] == ',') {
    return members(s, end + 1);
  }
  return end;
}

int elements(const string& s, int at) {
  int part = 0;
  parts.push_back("["+ to_string(part) + "]");
  int end = value(s, at);
  auto path = get_path(parts);
  if(paths.count(path)) {
    paths[path] = s.substr(at, end -at);
  }
  parts.pop_back();
  while(s[end] == ',') {
    int lend = end + 1;
    part++;
    parts.push_back("["+ to_string(part) + "]");
    end = value(s, end + 1);
    auto path = get_path(parts);
    if(paths.count(path)) {
      paths[path] = s.substr(lend, end - lend);
    }
    
    parts.pop_back();
  }
  return end;
}

int value(const string& s, int at) {
  int c = s[at];
  if(c == '{') {
    int end = members(s, at + 1);
    expect('}', s[end]);
    return end + 1;
  }else if(c == '[') {
    int end = elements(s, at + 1);
    expect(']', s[end]);
    return end + 1;
  }else if(isdigit(c)) {
    auto res = read_int(s, at);
    return res.second;
  }else if(c == '"') {
    auto res = read_str(s, at);
    return res.second;
  }
  // should not get here
  expect('=', '+');
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  string json; cin >> json;
  int n; cin >> n;
  vector<string> ans(n);
  for(int i = 0; i < n; i++) {
    string p; cin >> p;
    ans[i] = p;
    paths[p] = kSentinal; // sentinal value
  }

  value(json, 0);

  for(auto const& s: ans) {
    cout << paths[s] << '\n';
  }
}
