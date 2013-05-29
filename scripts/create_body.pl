#!/usr/bin/perl
######################################################
#	Desc: The script generate a c++ body for a header							#
#	Subscription: after this bracket:} never be ";" symbol , just if it is the end of a class!!  	#
#	Param: -the header file name										#
#

##################VARIABLES#############################
$namespace="";		#the namespaces								#
$in=0;				#we are in a class specification					#
$offset=0;			#the last namespace offset in namespace variable		#
$counter=0;			#how many functions founded						#
######################################################
###################CONSTANTS FOR REG EXPS##################
$reg_typeName="(const)?\\s*[:_a-zA-Z]+[:_a-zA-Z0-9]*\\s*(const)?\\s*(\\*)?\\s*(\\&)?";	#
$reg_varName="[a-zA-Z_]+[_a-zA-Z0-9]*";						#
$reg_funcName="($reg_varName::)*[_a-zA-Z]+[_a-zA-Z0-9]*";						#
$reg_operator="[\\*\\(\\)\\[\\]\\/+-=><!]";					#
$reg_number="[0-9]";										#
$reg_digit="([0-9]+\\.?[0-9]*)|([0-9]*\\.?[0-9]+)";			#
$reg_string="\\\".*\\\"";									#
######################################################

if(@ARGV==0)
{
	print "I need a file: Header file name";
	goto END;
}

open(HEADER,"<",$ARGV[0]) or die("I can't open: ".$ARGV[0]);
opendir(DIR,".");
@files=readdir(DIR);
closedir(DIR);
for(@files)
{
	if($_ eq substr($ARGV[0],0,length($ARGV[0])-1)."cpp")
	{
		print "The file has already exists, if I continoue the program the file's data will be lost!\n";
		print "can I continoue?(y/n): ";
		$ans=lc(<STDIN>);
		if($ans=~/n/)
		{
			goto END;
		}
		break;
	}
}
my $fileName = substr($ARGV[0],0,length($ARGV[0])-1)."cpp";
if (@ARGV > 1)
{
	$fileName = $ARGV[1];
}
open(BODY, ">", $fileName);



print "founded functions:\n";
print BODY "#include \"$ARGV[0]\"\n";
print BODY "\n\n";
while(<HEADER>)
{
	if($_=~/\s*class\s+($reg_varName)\s*.*/ && !$in)
	{
		$offset=length($namespace);
		my $tmp=$1;
		#print $tmp;
		$tmp=~s/^\s//;
		$tmp=~s/\s$//;
		#print $tmp;
		$namespace.=$tmp."::";
		$in=1;
	}
	if($_=~/\s*struct\s+($reg_typeName)\s*.*/ && !$in)
	{
		$offset=length($namespace);
		my $tmp=$1;
		#print $tmp;
		$tmp=~s/^\s//;
		$tmp=~s/\s$//;
		#print $tmp;
		$namespace.=$tmp."::";
		$in=1;
	}
	if($_=~/^\s*namespace\s+($reg_typeName)\s*/)
	{
		$offset=length($namespace);
		my $tmp=$1;
		#print $tmp;
		$tmp=~s/^\s//;
		$tmp=~s/\s$//;
		#print $tmp;
		$namespace.=$tmp."::";
	}
	if($_=~/}\s*;/)
	{
		$in=0;
		$namespace=substr($namespace,0,$offset);
	}
	if($_=~/^\s*(?<friend>friend(\s+))?(?<virtual>virtual\s+)?(?<static>static\s+)?(?<type>$reg_typeName(\s+))?(?<funcName>$reg_funcName$reg_operator{0,2})\s*\((?<other>(\s*$reg_typeName\s+$reg_varName(=\s*(($reg_digit)|($reg_string)))?\s*,?)*)\)\s*(?<const>const)?\s*;?\s*$/)
	{
		if($in)
		{
			++$counter;
			my $friend="";
			my $type="";
			my $funcName="";
			my $const=$+{const};
			my $other=$+{other};
			print "$+{friend}$+{virtual}$+{static}$+{type}$namespace$+{funcName}";
			print BODY "$+{type}$namespace$+{funcName}";
			$other=~s/=\s*(($reg_digit)|($reg_string))//;
			print "($other) $const\n";
			print BODY "($other) $const\n";
			print BODY "{\n";
			print BODY "\t\n";
			print BODY "}\n\n";
		}
	}
}
print "=============================================================\n";
print "Founded functions number: $counter\n";
close(HEADER);
close(BODY);
END:
