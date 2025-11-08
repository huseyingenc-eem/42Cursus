#!/usr/bin/perl
use strict;
use warnings;

# Parametreler: max, count, filename
my ($max, $count, $filename) = @ARGV;

# Kullanım ve temel doğrulamalar
if (not defined $max or not defined $count or not defined $filename) {
    die "Kullanım: perl random_number.pl <maksimum_sayi> <adet> <dosya_adi>\n";
}
$max    =~ /^\d+$/ or die "Hata: <maksimum_sayi> pozitif bir tam sayı olmalı.\n";
$count  =~ /^\d+$/ or die "Hata: <adet> pozitif bir tam sayı olmalı.\n";
$max  > 0          or die "Hata: <maksimum_sayi> 0'dan büyük olmalı.\n";
$count > 0          or die "Hata: <adet> 0'dan büyük olmalı.\n";

# Eğer istenilen sayı aralıktan fazlaysa uyarı
if ($count > $max) {
    die "Hata: $count adet unique sayı üretmek için maksimum değer en az $count olmalı (şu an: $max).\n";
}

# İsteğe bağlı: manuel seed (genelde gerekmez ama tutarlı olsun)
srand();

# Dosyayı yazma modunda aç
open(my $fh, '>', $filename) or die "Dosya açılamadı: $filename -> $!\n";

# UNIQUE sayıları üret (duplicate kontrolü ile)
my %seen;
my @nums;

while (@nums < $count) {
    my $num = int(rand($max));
    
    # Eğer bu sayı daha önce görülmediyse ekle
    unless (exists $seen{$num}) {
        push @nums, $num;
        $seen{$num} = 1;
    }
}

# Yan yana (tek satır) yaz: arada boşluk
print $fh join(' ', @nums), "\n";

close($fh) or warn "Dosya kapatılırken uyarı: $!";

print "$count adet UNIQUE sayı tek satır halinde '$filename' dosyasına yazıldı.\n";
