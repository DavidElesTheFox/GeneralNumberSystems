if(@ARGV<1)
{
	print "I need the testCase name!\n";
	goto END;
}
my $tc_name=$ARGV[0];
my $Dir=".";
if(@ARGV>1)
{
	
	$Dir=$ARGV[1];
}

open (MAIN,">", "$Dir/main.cpp" ) or die("I can't open the file: $Dir/$tc_name");

print MAIN "#include \"$tc_name.h\"\n";
print MAIN "\n\n\n";
print MAIN "int main()\n";
print MAIN "{\n\t";
print MAIN "$tc_name test;\n\t";
print MAIN "test.run();\n";
print MAIN "}\n\n";
close (MAIN);
END:
