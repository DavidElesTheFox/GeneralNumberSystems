#########################################################
#	 The script make a temp file, which includes	#
#	 the assert's comment				#
#	 Parameter:					#
#		-fileName (body, cpp file name)		#
#########################################################

$fileName=$ARGV[0]or die("I can't open: ".$ARGV[0]);
open(BODY,"<",$fileName);
if(@ARGV<2)
{
	open(TMPBODY,">","tmp_".$fileName)or die("I can't open: "."tmp_".$fileName);
}else
{
	open(TMPBODY,">",$ARGV[1])or die("I can't open: ".$ARGV[1]);
}
$i=0;			#counteer
$functionName="null";

while(<BODY>)
{
    if($_=~/\s*void\s*([\w:]*)\s*\(.*\).*/)
    {
	$functionName=$1;
    }
    if($_=~/.*(assert\w*)\(.*\).*/)
    {
	print TMPBODY "setComment(\"at: $functionName(line:".$i."[".$1."])\");\n";
    }
    print TMPBODY $_;
    ++$i;
}
close(BODY);
close(TMPBODY);
