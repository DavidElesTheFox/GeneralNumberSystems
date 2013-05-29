#!/usr/bin/perl
#########################################################################
#									#
#	This script make a run_... file, which I get in parameter	#
#	Prameter:							#
#		-the file name						#
#########################################################################

my $fileName=$ARGV[0];

open(HEADER,"<",$fileName) or die("I can't open the file: ".$fileName);

my @functions;
my $i=0;		#iterator for functions
my $namespace="";
while(<HEADER>)
{
    if($_=~/\s?using\s(\w).*/)
    {
    
    }elsif($_=~/\s?namespace\s(\w*).*/)
    {
		$namespace.=$1."::";
    }elsif($_=~/\s?class\s(\w*):?.*/)
    {
		$namespace.=$1."::";
    }elsif($_=~/\s?void\s(test\w*)\(\).*/)
    {
		$functions[$i]=$1;
		$i++;
    }
}


close HEADER;

if(@ARGV<2)
{
	$fileName =~ s/(.*[\\\/])(.*)\.h/$1run_$2.cpp/;
	open(RUN,">",$fileName) or die("I can't open the file: ".$fileName);
}else
{
	open(RUN,">",$ARGV[1])or die("I can't open the file!") or die("I can't open the file: ".$ARGV[1]);
}

my @l_path_file_name=split("/",$fileName);
my $l_rel_file_path=$l_path_file_name[@l_path_file_name-1];

$body="";

$body.="void ".$namespace.'run()'."\n{\n";
$body.="\tbool tmp = true;\n";
for(my $i=0;$i<@functions-1;++$i)
{
    if($functions[$i]=~/\w/)
    {
			$body.="\ttry\n";
			$body.="\t{\n";
			$body.="\t\t$functions[$i]();\n";
			$body.="\t\tif(isOk())\n";
			$body.="\t\t\t".'std::cout<<"\tOK................'.$functions[$i].'"<<std::endl;'."\n";
			$body.="\t\t".'else'."\n";
			$body.="\t\t\t".'std::cout<<"\tNOK...............'.$functions[$i].'"<<std::endl;'."\n";
			$body.="\t\t".'tmp = tmp && isOk();'."\n";
			$body.="\t\t".'ok = true;'."\n";
			$body.="\t}\n";
			$body.="\tcatch(Exceptions::Exception& ex)\n";
			$body.="\t{ std::cout<<\"".$functions[$i]."Exception occured: \" << ex <<std::endl; }\n";
			$body.="\tcatch(...)\n";
			$body.="\t{ std::cout<<\"".$functions[$i]."Unknown exception\"<<std::endl;  }\n";
			$body.="\n";
	    
    }
}
if(@functions>0)
{
	$body.="\ttry\n";
	$body.="\t{\n";
	$body.="\t\t$functions[@functions - 1]();\n";
	$body.="\t\tif(isOk())\n";
	$body.="\t\t\t".'std::cout<<"\tOK................'.$functions[@functions - 1] .'"<<std::endl;'."\n";
	$body.="\t\t".'else'."\n";
	$body.="\t\t\t".'std::cout<<"\tNOK...............'.$functions[@functions - 1] .'"<<std::endl;'."\n";
	$body.="\t\t".'tmp = tmp && isOk();'."\n";
	$body.="\t\t".'ok = true;'."\n";
	$body.="\t}\n";
	$body.="\tcatch(Exceptions::Exception& ex)\n";
	$body.="\t{ std::cout<<\"".$functions[@functions - 1].": Exception occured: \" << ex <<std::endl; }\n";
	$body.="\tcatch(...)\n";
	$body.="\t{ std::cout<<\"".$functions[@functions - 1].": Unknown exception\"<<std::endl;  }\n";
	$body.="\n";
}else
{
	$body.="\n";
}
$body.="}\n";

print RUN $body;
close RUN;

#print $body;
