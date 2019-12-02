use List::MoreUtils qw(uniq);
@hrefs = ();
#open $in, '<', '331';
while (<>) {
    while (/<\s*?a.*?\shref="((http|https|ftp)?:\/\/)?(\w+.*?)(:|\/|").*?>/g) {
        push(@hrefs, $3);
    }
}
@hrefs = uniq sort @hrefs;
foreach $href (@hrefs) {
    print $href;
    print "\n";
}
