#!/usr/bin/perl
# This script is set the install dir to the second argument
# in all of CMakeLists.txt file from the given directory 
# (first argument)

die "I need the start Directory" if (@ARGV < 1);
die "I need the new baseDir full path" if (@ARGV < 2);

modif_all($ARGV[0], $ARGV[1]);


sub modif_all
{
	my $dir = $_[0];
	my $baseDir = $_[1];
#print "$baseDir\n";
	modif($dir, $baseDir);
	opendir(my $dh, $dir);
	my @files=readdir $dh;
	closedir $dh;
	foreach my $file (@files)
	{
		next if($file =~ /\./);
		if(-d "$dir/$file")
		{
			modif_all("$dir/$file", $baseDir);
		}
	}
}

sub modif
{
	my $dir = $_[0];
	my $baseDir = $_[1];
	opendir(my $dh, $dir);
	my @files = readdir $dh;
	closedir $dh;
	foreach my $file (@files)
	{
		if ($file =~ /CMakeLists.txt/)
		{
			open (FILE,"<","$dir/$file");
			my @lines = <FILE>;
			close (FILE);
			print "\t\e[0;31mMODIFY:\e[0;32m $dir/$file \e[0m\n";
			open (FILE, ">", "$dir/$file");
			foreach my $line (@lines)
			{
				if ($line =~ /set \(install_dir/)
				{
				  print FILE "set (install_dir \"$baseDir\")\n";
				}
				else
				{
        	print FILE "$line";
				}
			}
			close (FILE);
		}
	}
}
