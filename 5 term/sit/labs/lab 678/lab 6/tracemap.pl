#!/usr/bin/perl -w
#
use Net::IP qw(:PROC);

our $traceroute_options="-q1 -n -I";
our $hops_to_highlight=4;
our $verbose =1;
our $prefixes="prefixes.txt";
our $scale=1;

our $dot_file="tracemap.dot";
our $svg_file="tracemap.svg";
our $png_file="tracemap.png";

#our @printed_hops;
our $graph="";
our $hop_id = 0;
our %hop_id;

our $previous_hop;
our $previous_time;
our $hop;
our $time;
our $ttl;

our %color_table=qw(
10.0.0.0/16 seagreen2
10.1.0.0/16 seashell2
10.2.0.0/16 sienna2
10.3.0.0/16 skyblue2
10.4.0.0/16 slateblue2
10.5.0.0/16 slategray2
10.6.0.0/16 snow1
10.7.0.0/16 springgreen1
10.8.0.0/16 steelblue1
);

our @prefixes;

sub load_prefixes
{
    my @prefixes=();
    open(PREFIXES, $prefixes);
    while (<PREFIXES>) { chomp; push @prefixes, $_;};
    close(PREFIXES);
    return @prefixes;
}

sub ip_in_range
{
    my $ip=shift;
    my $range_found=0;
    for my $range (@_) {
        my ($range_ip, $range_prefix) = split m@/@, $range;
        my ($ip1, $ip2) = ip_prefix_to_range($range_ip, $range_prefix,4);
#        print "$range\n";
        $range_found=ip_bincomp(ip_iptobin($ip1,4),'lt',ip_iptobin($ip,4))
            && ip_bincomp(ip_iptobin($ip,4),'lt',ip_iptobin($ip2,4));
        if ($range_found) {
            return $range;
        }
    }
    return 0;
}

sub color_of_ip($)
{
    my $ip = shift;
    for $range (keys %color_table) {
       if (ip_in_range($ip,$range)) {
            return $color_table{"$range"};
        }
    }
    return "indigo";
}

sub print_hop($)
{
    $hop = shift;
    unless (defined($hop_id{$hop})) {
        $hop_id++;
        $color="";
        $shape="";
        if (ip_in_range($hop, @prefixes)) {
            $color=",color=green"
        }
        $color=",color=".color_of_ip($hop);
        if ($ttl == $hops_to_highlight+1) {
            $shape=",shaper=rectangle"
        }
        $graph .= "hop$hop_id [ label=\"$hop\"$color$shape];";
        $hop_id{$hop} = $hop_id;
    }
}

sub time_to_len($$)
{
    $a=shift;
    $b=shift;
    $l=$a-$b;
    $l = 0.25 if $l<0.25;
    return (3+1.2*log($l))*0.3285*$scale;
}
sub say
{
    print @_ if $verbose;
}

sub ping_sweep($)
{
    my $net = shift;
    my @res;
    say("Doing ping sweep of the $net IP-addresses block");
    open(NMAP, "nmap -sP $net|grep 'appears to be up' | awk '{print \$2}'|")
        or die "can't make ping sweep of $net. Have you nmap installed?\n$!";
    while (<NMAP>) {
        chomp;
        push (@res, ($_));
        say(".");
    }
    say("Done. $#res host(s) found.\n");
    return @res;
}

sub dns_axfr($)
{
    my @res;
    my ($zone,$ns) = split /@/;
    if ($ns eq '') {
    }
    else 
    {
        say("Doing axfr of the zone $zone from the server $ns\n");
        open(DIG, "dig \@$ns axfr $zone | awk '/\tA\t/ {print \$1}' |")
            or die "can't make axfr of the zone $zone from the server $ns. Have you dig installed?\n$!";
        while (<DIG>) {
            chomp;
            push (@res, ($_));
        }
        say("Done. $#res host(s) found.\n");
        return @res;
    }
}

my @dests=();
while(<>)
{
    chomp;
    next if /^#/;
    if (m@http:@) {
    }
    elsif (m@/@) {
        push(@dests,ping_sweep($_))
    }
    elsif (m'@') {
        push (@dests,dns_axfr($_))
    }
    else {
        push(@dests,($_));
    }
}

@prefixes=load_prefixes();

for $dest (@dests)
{
    say("Tracing path to $dest");
    open (TRACE,"traceroute $traceroute_options $dest|")
        or die "Can't run traceroute:$!";
    my $hop='';
    $ttl=0;
    my $total=0;
    while (<TRACE>) {
        chomp;
        next if not /ms/;
        say(".");
        $ttl++;
        s@^\s*@@;
        $previous_hop=$hop;
        $previous_time=$time;
        my $a;
        ($a, $hop, $time) = split(/\s+/, $_, 3);
        $time =~ s/\s*ms\s*$//;
        $total += $time;
        if ($previous_hop eq '') {
            print_hop($hop);
            $graph =~ s@color=[^],]*[],]@@;
            $graph =~ s@(\ label=\")[^"]*(\".*?)$@fontsize=10,color=red,style=filled,label="(YOU)$2@;
        }
        elsif (not defined $hop_id{$hop} ) {
            print_hop($previous_hop);
            print_hop($hop);
            $graph .= "hop".$hop_id{$previous_hop}." -- hop".$hop_id{$hop}.
            " [label=\"".sprintf("%1.2f",+$time-$previous_time)."\",len=".time_to_len($time,$previous_time)."];\n";
        }
    }
    $graph =~ s@(\ label=\")[^"]*(\".*?)$@fontsize=8,style=filled,label=\"$dest$2@;
    close(TRACE);
    say("Done [last $time, total $total]\n");
}
#$temp=rand.rand;

open (DOT, ">$dot_file")
    or die "can;t open dot file file for writing: $!";
print DOT <<EOF;
graph G {
    margin =1 ;
    node [fontname=times,fontsize=7,shape=circle,width=0.1,height=0.1,fixedsize=true,color=blue];
    edge [fontname=times,fontsize=5,color=black];
$graph
}
EOF
close(DOT);

print `neato -o $png_file -Tpng $dot_file > /dev/null 2>&1; neato -o $svg_file -Tsvg $dot_file > /dev/null 2>&1 `
    or die "can't run neato: $!;\ngraphviz is installed?\nYou can tracemap.dot to the hosts where graphviz in installed and run\nneato -o tracemap.png -Tpng tracemap.dot"

