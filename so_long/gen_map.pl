#!/usr/bin/perl
use strict;
use warnings;
use List::Util qw(shuffle);

# Kullanım:
#   ./gen_map.pl <width> <height> <collectibles> [seed] [--braid=0.30] [--turn=0.75] [--noise=0.02]
# Öneri:
#   width/height >= 5 ve tercihen TEK sayılar (31x17 gibi)
# Paramlar:
#   --braid   : 0..1 arası, dead-end'lerin ne kadarını kırıp döngü ekleyelim? (varsayılan 0.30)
#   --turn    : 0..1 arası, yön değiştirmeyi ne kadar teşvik edelim? (1 = her fırsatta dön)
#   --noise   : 0..0.2 arası küçük bir değer; iç duvarlardan rastgele boşluk açma oranı (bağlanırlık korunur)

die "Usage: $0 <width> <height> <collectibles> [seed] [--braid=f] [--turn=f] [--noise=f]\n"
  unless (@ARGV >= 3);

my ($W, $H, $C, $SEED, @opts) = @ARGV;
my $BRAID = 0.30;
my $TURNB = 0.75;
my $NOISE = 0.00;

# opsiyonları oku
for my $o (@opts) {
    if ($o =~ /^--braid=(\d*\.?\d+)$/) { $BRAID = $1 + 0; next; }
    if ($o =~ /^--turn=(\d*\.?\d+)$/)  { $TURNB = $1 + 0; next; }
    if ($o =~ /^--noise=(\d*\.?\d+)$/) { $NOISE = $1 + 0; next; }
}

$SEED //= time;
srand($SEED);

die "width and height must be >= 5\n" unless ($W >= 5 && $H >= 5);
die "collectibles must be >= 1\n"     unless ($C >= 1);
$BRAID = 0   if $BRAID < 0;  $BRAID = 1   if $BRAID > 1;
$TURNB = 0   if $TURNB < 0;  $TURNB = 1   if $TURNB > 1;
$NOISE = 0   if $NOISE < 0;  $NOISE = 0.2 if $NOISE > 0.2;

# --- Izgara: dis duvarlar 1, ic kisimlar 1 ile dolu ---
my @grid = map { [('1') x $W] } (0..$H-1);

# Yardımcılar
sub inb    { my ($y,$x)=@_; return ($y>0 && $x>0 && $y<$H-1 && $x<$W-1); }
sub neigh4 {
    my ($y,$x)=@_;
    return ([$y-1,$x],[ $y+1,$x],[ $y,$x-1],[ $y,$x+1]);
}
sub neigh4_2step {
    my ($y,$x)=@_;
    return ([$y-2,$x, -1,0], [ $y+2,$x, 1,0], [ $y,$x-2, 0,-1], [ $y,$x+2, 0,1]);
}
sub count_open_neighbors {
    my ($y,$x)=@_;
    my $c=0;
    for my $n (neigh4($y,$x)) { my ($ny,$nx)=@$n; $c++ if inb($ny,$nx) && $grid[$ny][$nx] eq '0'; }
    return $c;
}

# ---- Maze carving: recursive backtracker + TURN BIAS ----
my ($sy,$sx) = (1,1);
$grid[$sy][$sx] = '0';
my @stack = ([$sy,$sx, 0,0]); # (y,x, prev_dy, prev_dx)

while (@stack) {
    my ($y,$x,$pdy,$pdx) = @{$stack[-1]};

    my @cand;
    for my $d (neigh4_2step($y,$x)) {
        my ($ny,$nx,$hy,$hx) = @$d;
        next unless inb($ny,$nx);
        if ($grid[$ny][$nx] eq '1') {
            # Ağırlıklandırma: önce aynı yöne devam etme isteğini azalt (TURNB yüksekse dönmeyi tercih et)
            my ($dy,$dx) = ($ny-$y, $nx-$x);
            my $same_dir = ($pdy==$dy && $pdx==$dx) ? 1 : 0;
            my $w = $same_dir ? (1.0-$TURNB) : (0.5+$TURNB/2.0);
            push @cand, [$ny,$nx,$hy,$hx,$w];
        }
    }

    if (!@cand) { pop @stack; next; }

    # Ağırlığa göre seçim
    my $sum = 0; $sum += $_->[4] for @cand;
    my $r = rand($sum);
    my $pick;
    for (@cand) { if ($r <= $_->[4]) { $pick = $_; last } $r -= $_->[4]; }
    $pick //= $cand[0];
    my ($ny,$nx,$hy,$hx,$w) = @$pick;

    # Aradaki duvarı ve hedefi oy
    $grid[$y+$hy][$x+$hx]='0';
    $grid[$ny][$nx]='0';
    push @stack, [$ny,$nx, $ny-$y, $nx-$x];
}

# ---- Braid (dead-end kırma) ----
if ($BRAID > 0) {
    for my $y (1..$H-2) {
        for my $x (1..$W-2) {
            next unless $grid[$y][$x] eq '0';
            my $deg = count_open_neighbors($y,$x);
            next unless $deg == 1;           # dead-end
            next unless rand() < $BRAID;     # belli oranda kır
            # Açılabilecek komşu duvarlardan birini seç
            my @walls;
            for my $n (neigh4($y,$x)) {
                my ($ny,$nx)=@$n;
                next unless inb($ny,$nx);
                push @walls, [$ny,$nx] if $grid[$ny][$nx] eq '1';
            }
            @walls = shuffle(@walls);
            if (@walls) {
                my ($wy,$wx) = @{$walls[0]};
                # Dış duvarı asla kırma:
                next if ($wy==0 || $wx==0 || $wy==$H-1 || $wx==$W-1);
                $grid[$wy][$wx] = '0';
            }
        }
    }
}

# ---- Noise (rastgele iç duvar kırma) ----
if ($NOISE > 0) {
    for my $y (1..$H-2) {
        for my $x (1..$W-2) {
            next unless $grid[$y][$x] eq '1';
            next unless rand() < $NOISE;
            # Sadece iki karşılıklı açık komşusu varsa kır (köprü etkisi)
            my $up    = ($grid[$y-1][$x] eq '0') ? 1 : 0;
            my $down  = ($grid[$y+1][$x] eq '0') ? 1 : 0;
            my $left  = ($grid[$y][$x-1] eq '0') ? 1 : 0;
            my $right = ($grid[$y][$x+1] eq '0') ? 1 : 0;
            my $pairs = (($up && $down) || ($left && $right));
            next unless $pairs; # saçma boşluk açma, bir bağlantı olsun
            $grid[$y][$x] = '0';
        }
    }
}

# ---- BFS: en uzak noktaya E, P sabit/uygun bir boşluk ----
sub bfs_dist {
    my ($sy,$sx)=@_;
    my @dist = map { [(-1) x $W] } (0..$H-1);
    my @q = ([$sy,$sx]);
    $dist[$sy][$sx] = 0;
    my @dirs4 = ([1,0],[-1,0],[0,1],[0,-1]);
    my ($fy,$fx)=($sy,$sx);
    while (@q) {
        my ($y,$x)=@{shift @q};
        ($fy,$fx)=($y,$x) if $dist[$y][$x] > $dist[$fy][$fx];
        for my $d (@dirs4) {
            my ($ny,$nx)=($y+$d->[0],$x+$d->[1]);
            next if $ny<0 || $nx<0 || $ny>=$H || $nx>=$W;
            next if $grid[$ny][$nx] eq '1';
            next if $dist[$ny][$nx] != -1;
            $dist[$ny][$nx] = $dist[$y][$x] + 1;
            push @q, [$ny,$nx];
        }
    }
    return ($fy,$fx,\@dist);
}

# P konumu: (1,1) boş değilse ilk boşluğu bul
my ($py,$px) = (1,1);
if ($grid[$py][$px] eq '1') {
    OUTER: for my $y (1..$H-2) {
        for my $x (1..$W-2) {
            if ($grid[$y][$x] eq '0') { ($py,$px)=($y,$x); last OUTER; }
        }
    }
}
my ($ey,$ex,$dist_ref) = bfs_dist($py,$px);

# Collectible'lar: erişilebilir boşluklardan
my @empties;
for my $y (1..$H-2) {
    for my $x (1..$W-2) {
        next if ($y==$py && $x==$px);
        next if ($y==$ey && $x==$ex);
        next if ($grid[$y][$x] ne '0');
        next if ($dist_ref->[$y][$x] < 0);
        push @empties, [$y,$x];
    }
}
@empties = shuffle(@empties);
$C = 1 if $C < 1;
$C = scalar(@empties) if $C > scalar(@empties);

# Yerleştir
$grid[$py][$px] = 'P';
$grid[$ey][$ex] = 'E';
for (my $i=0; $i<$C; $i++) {
    my ($cy,$cx) = @{$empties[$i]};
    $grid[$cy][$cx] = 'C';
}

# Güvence: dış sınırlar duvar
for my $x (0..$W-1) { $grid[0][$x]='1'; $grid[$H-1][$x]='1'; }
for my $y (0..$H-1) { $grid[$y][0]='1'; $grid[$y][$W-1]='1'; }

# Çıktı
for my $y (0..$H-1) { print join('', @{$grid[$y]}), "\n"; }
