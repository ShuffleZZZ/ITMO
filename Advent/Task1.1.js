var sum = 0;

for (var i = 0; i < 100; i++) {
    var line = parseInt(readline());
    line = Math.floor(line / 3) - 2;
    sum -= -line;
}

print(sum);
