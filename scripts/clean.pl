#!/usr/bin/perl

clean(".");

sub clean($)
{
  my $dirName = $_[0];
  opendir (my $dir, $dirName);
  my @list = readdir ($dir);
  closedir ($dir);

  foreach my $act (@list)
  {
    if(-d $dirName."/".$act && $act ne "." && $act ne "..")
	{

	  if ($act=~/build/)
	  {
		system('rm', '-r', "$dirName/$act");
		print "Clean: $dirName/$act\n";
		system('mkdir', "$dirName/build");
	  }
	  else
	  {
		clean("$dirName/$act");
	  }
	}
  }
}
