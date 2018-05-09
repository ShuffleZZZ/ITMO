var abstractOper = function (first) {
    return function () {
        var temp = arguments;
        return function () {
            var args = [];
            for (var i = 0; i < temp.length; i++) {
                args.push(temp[i].apply(null, arguments));
            }
            return first.apply(null, args);
        }
    }
};

var cnst = function (x) {
    return function () {
        return x;
    }
};

var variable = function (x) {
    return function () {
        if (x === "x") {
            return arguments[0];
        } else if (x === "y") {
            return arguments[1];
        } else if (x === "z") {
            return arguments[2];
        }
    }
};

var negate = abstractOper(function (a) {
    return -a
});

var cube = abstractOper(function (a) {
    return Math.pow(a, 3)
});

var cuberoot = abstractOper(function (a) {
    return Math.pow(a, 1 / 3)
});

var add = abstractOper(function (a, b) {
    return a + b;
});

var subtract = abstractOper(function (a, b) {
    return a - b;
});

var multiply = abstractOper(function (a, b) {
    return a * b;
});

var divide = abstractOper(function (a, b) {
    return a / b;
});