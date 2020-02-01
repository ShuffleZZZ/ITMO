var list = readline().split(",");
for (var i = 0; i < list.length; i++) {
    list[i] = parseInt(list[i]);
}

list[1] = 12;
list[2] = 2;
optcode = 0;

while (true) {
    if (list[optcode] === 1) {
        list[list[optcode + 3]] = list[list[optcode + 1]] + list[list[optcode + 2]];
        optcode += 4;
    } else if (list[optcode] === 2) {
        list[list[optcode + 3]] = list[list[optcode + 1]] * list[list[optcode + 2]];
        optcode += 4;
    } else {
        break;
    }
}

print(list[0]);
