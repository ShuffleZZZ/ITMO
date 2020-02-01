var list = readline().split(",");
for (var i = 0; i < list.length; i++) {
    list[i] = parseInt(list[i]);
}

for (var noun = 99; noun >= 0; noun--) {
    for (var verb = 10; verb >= 0; verb--) {
        var tempList = [];
        for (var i = 0; i < list.length; i++) {
            tempList.push(list[i]);
        }

        var optcode = 0;
        tempList[1] = noun;
        tempList[2] = verb;

        while (true) {
            if (tempList[optcode] === 1) {
                tempList[tempList[optcode + 3]] = tempList[tempList[optcode + 1]] + tempList[tempList[optcode + 2]];
                optcode += 4;
            } else if (tempList[optcode] === 2) {
                tempList[tempList[optcode + 3]] = tempList[tempList[optcode + 1]] * tempList[tempList[optcode + 2]];
                optcode += 4;
            } else {
                break;
            }
        }
        
        if (tempList[0] === 19690720) {
            print(100 * noun + verb);
        }
    }
}
