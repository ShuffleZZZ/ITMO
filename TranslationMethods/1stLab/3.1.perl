$empty = 0;
$start = 0;
#open $in, '<', '31in.txt';
while (<>) {
    if (/^\s*$/) {
        if ($start) {
            $empty = 1;
        }
    } else {
        if ($empty) {
            print "\n";
        }
        $start = 1;
        s/^\s+//g;
        s/\s+$//g;
        s/(\s)+\1/$1/g;
        print;
        print "\n";
        $empty = 0;
    }
}
