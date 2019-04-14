var INF = 1000000;

var n = readline();
var m = readline();
var pipeline = [];
var nums = [];
for (var i = 0; i < n; ++i) {
   nums[i] = [];
 }
for (var i = 0; i < m; ++i) {
  var args = readline().split(" ").map(function(x) {
    return parseInt(x);
  });
  pipeline.push([args[2], --args[0], --args[1], 0]);
  pipeline.push([args[2], args[1], args[0], 0]);
  nums[args[0]].push(2 * i);
  nums[args[1]].push(2 * i + 1);
}

var came = [];
var prev = [];

for (var i = 0; i < n; ++i) {
  came.push(false);
  prev.push(-1);
}

var bfs = function () {
  for (var i = 0; i < n; ++i) {
    came[i] = false;
    prev[i] = -1;
  }
  var q = [];
  q.push(0);
  came[0] = true;
  var flow = INF;
  while (q.length !== 0) {
    var v = q.shift();
    for (var i = 0; i < nums[v].length; ++i) {
      var gap = pipeline[nums[v][i]][0] - pipeline[nums[v][i]][3];
      var pipe = pipeline[nums[v][i]][2];
      if (came[pipe] === false && gap > 0) {
        if (gap < flow) {
          flow = gap;
        }
        q.push(pipe);
        came[pipe] = true;
        prev[pipe] = nums[v][i];
      }
    }
  }
  if (came[n - 1] === true) {
    return flow;
  } else {
    return 0;
  }
};

var dfs = function (v, flow) {
  if (v === n - 1) return flow;
  for (var i = 0; i < nums[v].length; ++i) {
    if (pipeline[nums[v][i]][3] > 0) {
      var volume = dfs(pipeline[nums[v][i]][2],
          Math.min(flow, pipeline[nums[v][i]][3]));
      pipeline[nums[v][i]][3] -= volume;
      return volume;
    }
  }
  return 0;
};

var volume = bfs();
while (volume != 0)
{
  for (var v = n - 1; v != 0; v = pipeline[prev[v]][1]) {
    pipeline[prev[v]][3] += volume;
    pipeline[prev[v] ^ 1][3] -= volume;
  }
  volume = bfs();
}
var volumes = [];
for (var i = 0; i < 2 * m; i += 2) {
  volumes.push(pipeline[i][3]);
}
volume = 0;
var tmp = dfs(0, INF);
while (tmp !== 0) {
  volume += tmp;
  tmp = dfs(0, INF);
}
print(volume);
for (var i = 0; i < volumes.length; ++i) {
  print(volumes[i]);
}
