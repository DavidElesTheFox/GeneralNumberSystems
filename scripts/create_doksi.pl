use Data::Dumper;

my $g_scope = 0; 	#0-private
					#1-protected
					#2-public
my $g_debug = 0;
my $g_short = 1;
my @g_class;	
my $g_c_counter = 0;
my $g_f_counter = 0;
my $g_b_counter = 0;
my $E_FUNC_NAME = "func_name";
my $E_SIMPLE = "simple";
my $E_FUNCTIONS = "functions";
my $E_DESC = "main_description";
my $E_PARAMS = "params";
my $E_NAME = "name";
my $E_DESC = "desc";
my $E_RETURN_VAL = "return_val";
my $E_MEMBERS = "members";
my $E_BASE_CLASSES = "base_classes";
my $E_SCOPE = "scope"; #0-private; 1-protected ; 2-public
my $E_THROW = "throw";

################################# FUNCTIONS ############################
sub trim_p;
sub chop_comma_p;
sub load_class_p;
sub write_class_tex_p;
sub write_class_description_tex_p;
sub write_short_members_tex_p;
sub write_short_functions_tex_p;
sub write_members_tex_p;
sub write_functions_tex_p;	
sub write_function_details_p;
sub chop_last_lf_p;
sub last_word_p;
sub desc_2_tex_format;
################################## MAIN ################################

for(my $i = 2 ; $i < @ARGV;++$i)
{
	if($ARGV[$i] eq "-d")
	{
		$g_debug = 1;
	}
	elsif($ARGV[$i] eq "-l")
	{
		$g_short = 0;
	}
}

if(@ARGV<2)
{
	print "I need file  or directory name!\n";
	print "useage: [-d | -f] name\n";
	
	exit 1;
} 
if($ARGV[0] eq "-f")
{
	my $l_f = $ARGV[1];

	print "LOAD\n" if($g_debug);
	load_class_p($l_f);
	$l_f =~ s/(.*[\\\/])?(.*)\.(.*)/class_$2\.tex/;
	print "WRITE\n"  if($g_debug);
	write_class_tex_p($l_f, $g_c_counter - 1);
	print "WRITE END\n"  if($g_debug);
	print Dumper(@g_class) if($g_debug);
}
elsif($ARGV[0] eq "-d")
{
	my $l_d = $ARGV[1];
	opendir(my $l_dir, $l_d);
	my @l_files = readdir($l_dir);
	close ($l_dir);
	my $l_last_count = $g_c_counter;
	foreach my $l_file (@l_files)
	{
		if($l_file =~ /\.h$/)
		{
			my $l_header = "$l_d/$l_file";
			load_class_p($l_header);
			$l_file =~ s/(.*)\.(.*)/class_$1\.tex/;
			write_class_tex_p($l_file, $l_last_count, 0);
			for(my $i = $l_last_count + 1; $i < $g_c_counter;++$i)
			{
				write_class_tex_p($l_file, $i, 1);
			}
			$l_last_count = $g_c_counter;
		}
	}
	print Dumper(@g_class) if($g_debug);
}




################################ Functions #####################################
sub load_class_p
{
	my $l_file_name = $_[0];
	my @l_lines;

	#loading...
	my $R_BEGIN = "\\/\\*\\*";
	my $R_PARAM = "\@param";
	my $R_THROW = "\@throw";
	my $R_RET = "\@return";
	my $R_END = "\\*\\/";
	my $R_FUNC_END = "\\)";
	my $R_CLASS_END = "\\};";
	my $R_CLASS_BEGIN = "class";
	my $R_TEMPLATE = "template";
	my $R_PUBLIC = "public";
	my $R_PROTECTED = "protected";
	my $R_PRIVATE = "private";
	my $R_SIMPLE = "\@simple";


	my $l_in_f = 0;
	my $l_in_c = 0;
	my $l_in_c_desc = 0;
	my $l_param_count = 0;		#function params
	my $l_param_counter = 0;	#class params
	my $l_throw_count = 0;
	my $l_scope = 0;
	my $l_member_count = 0;

	open (FILE, "<", $l_file_name);
	my @l_lines = <FILE>;
	close(FILE);

	foreach my $l_line (@l_lines)
	{
		print $l_line."\n" if($g_debug);
		if($l_line =~ /$R_TEMPLATE/)
		{
			if( $l_in_c_desc == 2)
			{
				print "template\n" if($g_debug);
				$g_class[$g_c_counter]->{$E_NAME}  = trim_p($l_line)."\n";
			}
		}
		elsif($l_line =~ /($R_CLASS_BEGIN\s+\w+)\s*:?\s*([\w\s,:_]*)/)
		{
			if($l_in_c_desc == 2)
			{
				print "BEGIN CLASS $g_c_counter\n" if($g_debug);
				
				$g_class[$g_c_counter]->{$E_NAME} .= trim_p($1);
				print "CLASS NAME: $1-".$g_class[$g_c_counter]->{$E_NAME} ."\n" if($g_debug);
				if(not defined $g_class[$g_c_counter]->{$E_SIMPLE})
				{
					$g_class[$g_c_counter]->{$E_SIMPLE} = 0;
				}
				#print "class name: ".$g_class[$g_c_counter]->{$E_NAME}."\n" if($g_debug);
				my @l_part = split(" ",$2);
				foreach my $l_tmp(@l_part)
				{
					$l_tmp =~ s/,//;
					if($l_tmp eq "private" )
					{
						$l_scope = 0;
					}
					elsif($l_tmp eq "public")
					{
						$l_scope = 2;
					}
					else
					{
						$g_class[$g_c_counter]->{$E_BASE_CLASSES}[$g_b_counter]->{$E_NAME} = trim_p($l_tmp);
						$g_class[$g_c_counter]->{$E_BASE_CLASSES}[$g_b_counter]->{$E_SCOPE} = $l_scope;
						$l_scope = 0;
						$g_b_counter++;
					}
				}
				$g_b_counter = 0;
				$l_scope = 0;
				$l_member_count = 0;
				$l_param_count = 0;
				$l_param_counter = 0;
				$l_throw_count = 0;
				$l_in_c = 1;
				$l_in_c_desc = 3;
			}
		}
		elsif($l_line =~ /$R_CLASS_END/)
		{
			print "END CLASS\n" if($g_debug);
			$l_in_c = 0;
			$l_in_c_desc = 0;
			$g_c_counter++;
		}
		elsif($l_in_c ==1)
		{
			if($l_in_f == 1)
			{
				if($l_line =~ /$R_SIMPLE/)
				{
					$g_class[$g_c_counter]->{$E_FUNCTIONS}[$g_f_counter]->{$E_SIMPLE} = 1;
				}
				elsif($l_line =~ /$R_PARAM ([\w,]+)\s* (.+)$/)
				{
					print "param : $l_line\n" if($g_debug);
					$g_class[$g_c_counter]->{$E_FUNCTIONS}[$g_f_counter]->{$E_PARAMS}[$l_param_count]->{$E_NAME} = trim_p($1);
					$g_class[$g_c_counter]->{$E_FUNCTIONS}[$g_f_counter]->{$E_PARAMS}[$l_param_count]->{$E_DESC} = trim_p($2);
					$l_param_count++;
				}
				elsif($l_line =~ /$R_THROW ([\w:]+)\s* (.*)$/)
				{
					print "throw: $l_line\n" if($g_debug);
					$g_class[$g_c_counter]->{$E_FUNCTIONS}[$g_f_counter]->{$E_THROW}[$l_throw_count]->{$E_NAME} = trim_p($1);
					$g_class[$g_c_counter]->{$E_FUNCTIONS}[$g_f_counter]->{$E_THROW}[$l_throw_count]->{$E_DESC} = trim_p($2);
					$l_throw_count++
				}
				elsif($l_line =~ /$R_RET (.+)$/)
				{
					print "return: $l_line\n" if($g_debug);
					$g_class[$g_c_counter]->{$E_FUNCTIONS}[$g_f_counter]->{$E_RETURN_VAL} = trim_p($1);
				}
				elsif($l_line =~ /$R_END/)
				{
					print "end desc\n" if($g_debug);
					if(!(defined $g_class[$g_c_counter]->{$E_FUNCTIONS}[$g_f_counter]->{$E_SIMPLE}))
					{
						$g_class[$g_c_counter]->{$E_FUNCTIONS}[$g_f_counter]->{$E_SIMPLE} = 0;
					}
					$l_in_f = 2;
				}
				else
				{
					print "desc\n" if($g_debug);
					$g_class[$g_c_counter]->{$E_FUNCTIONS}[$g_f_counter]->{$E_DESC} .= trim_p($l_line)." ";
				}
			}
			elsif($l_in_f == 2)
			{
				
				$g_class[$g_c_counter]->{$E_FUNCTIONS}[$g_f_counter]->{$E_NAME} .= chop_comma_p(trim_p($l_line))."\n";
				print "file name\n" if($g_debug);
				if($l_line =~ /$R_FUNC_END/)
				{
					$g_class[$g_c_counter]->{$E_FUNCTIONS}[$g_f_counter]->{$E_SCOPE} = $l_scope;
					
					print "end func\n" if($g_debug);
					$g_f_counter++;
					$l_param_count = 0;
					$l_in_f = 0;
				}
			}
			elsif($l_line =~ /([\w\s;<>\*]+)\/\*\*\<(.*)\*\//)
			{
				print "MEMBER\n" if($g_debug);
				$g_class[$g_c_counter]->{$E_MEMBERS}[$l_member_count]->{$E_NAME} = chop_comma_p(trim_p($1));
				$g_class[$g_c_counter]->{$E_MEMBERS}[$l_member_count]->{$E_DESC} = trim_p($2);
				$g_class[$g_c_counter]->{$E_MEMBERS}[$l_member_count]->{$E_SCOPE} = $l_scope;
				$l_member_count++;
			}
			elsif($l_line =~ /$R_BEGIN/)
			{
				print "begin func\n" if($g_debug);
				$l_in_f = 1;
			}
			elsif($l_line =~ /$R_PUBLIC/)
			{
				print "public\n" if($g_debug);
				$l_scope = 2;
			}
			elsif($l_line =~ /$R_PROTECTED/)
			{
				print "protected\n" if($g_debug);
				$l_scope = 1;
			}
			elsif($l_line =~ /$R_PRIVATE/)
			{
				print "private\n" if($g_debug);
				$l_scope = 0;
			}
			
		}
		elsif($l_line =~ /$R_BEGIN/)
		{
			print "class desc in\n" if($g_debug);
			$l_in_c_desc = 1;
		}
		elsif($l_line =~ /$R_END/)
		{
			print "class desc out\n" if($g_debug);
			$l_in_c_desc = 2;
		}
		elsif($l_in_c_desc)
		{
			
			
			if($l_line =~ /$R_PARAM (\w+)\s*(.*)$/)
			{
				print "write class desc PARAM\n" if($g_debug);
				$g_class[$g_c_counter]->{$E_PARAMS}[$l_param_counter]->{$E_NAME} = chop_comma_p(trim_p($1));
				$g_class[$g_c_counter]->{$E_PARAMS}[$l_param_counter]->{$E_DESC} = trim_p($2);
				$l_param_count++;
			}
			elsif($l_line =~ /$R_SIMPLE/)
			{
				print "write class desc SIMPLE\n" if($g_debug);
				$g_class[$g_c_counter]->{$E_SIMPLE} = 1;
			}
			else
			{
				print "write class desc:\n" if($g_debug);
				$g_class[$g_c_counter]->{$E_DESC} .= trim_p($l_line)." ";
			}
		}
		
		
	}
}

sub write_class_tex_p
{
	my $l_file_name = $_[0];
	my $p_append = $_[1];
	print "FILE $l_file_name\n" if($g_debug);
	my $l_class_c = $_[1];
	if(!$p_append)
	{
		open (OUT, ">", $l_file_name);
	}
	else
	{
		open (OUT, ">>", $l_file_name);
	}
	#print OUT "\%auto generated by create_doksi\n";
	print OUT "\\section{Class ".last_word_p($g_class[$l_class_c]->{$E_NAME})."}\n";
	print OUT "\\index{Class ".last_word_p($g_class[$l_class_c]->{$E_NAME})."}\n";
	print OUT desc_2_tex_format($g_class[$l_class_c]->{$E_DESC});
	#	osztaly leiras
	write_class_description_tex_p($l_class_c);

	if(!$g_short)
	{
		print OUT "\\subsection{Függvények és adattagok rövid felsorolása}\n";
		print OUT "\n";
		
		write_short_members_tex_p($l_class_c);

		write_short_functions_tex_p($l_class_c);
		if(!$g_class[$l_class_c]->{$E_SIMPLE})
		{
			print OUT "\\subsection{Fontosabb függvények és adattagok részletes leírása}\n";
			print OUT "\n";
			write_members_tex_p($l_class_c);
			print OUT "\n";
			write_functions_tex_p($l_class_c);
		}
	}
	close OUT;
	
	
}


sub trim_p
{
	my $l_par = $_[0];
	#print "trim before: $l_par\n" if($g_debug);
	$l_par =~ s/^\s+//;
	$l_par =~ s/\s+$//;
	#print "trim after: $l_par\n" if($g_debug);
	return $l_par;
}

sub chop_comma_p
{
	my $l_par = $_[0];
	$l_par =~ s/;//;
	return $l_par;
}

sub last_word_p
{
	my $p_line = $_[0];
	
	my @l_spices = split(/[\s+\n]/, $p_line);
	print "LAST WORD: $p_line - ".$l_spices[@l_spices-1]."\n" if($g_debug);
	return $l_spices[@l_spices-1];
}

sub write_class_description_tex_p
{
	my $l_class_c = $_[0];
	if(defined $g_class[$l_class_c]->{$E_PARAMS})
	{
		print OUT "Az osztályhoz tartozó paraméterek:\n";
		
		my @l_tmp = $g_class[$l_class_c]->{$E_PARAMS};
		for( my $i = 0; $i < @l_tmp; ++$i )
		{
			if($i == 0)
			{
				print OUT "\\begin{enumerate}\n";
			}
			print OUT "\\item ".$g_class[$l_class_c]->{$E_PARAMS}[$i]->{$E_NAME}.": ";
			print OUT desc_2_tex_format($g_class[$l_class_c]->{$E_PARAMS}[$i]->{$E_DESC})."\n";
			if($i == @l_tmp - 1)
			{
				print OUT "\\end{enumerate}\n";
			}
		}
	}
	print OUT "\n";
	my $l_first = 1;
	if(defined $g_class[$l_class_c]->{$E_BASE_CLASSES})
	{
		print OUT "Az osztály ősosztájai:\n";
		print OUT "\\begin{enumerate}\n";
		
		
		for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_BASE_CLASSES}}; ++$i)
		{
			if(!$g_class[$l_class_c]->{$E_BASE_CLASSES}[$i]->{$E_NAME})
			{
				next;
			}
			if( $g_class[$l_class_c]->{$E_BASE_CLASSES}[$i]->{$E_SCOPE} == 2 )
			{
				if($l_first)
				{
					print OUT "\\item []Publikus ősosztályok:\n";
					print OUT "\\begin{itemize}\n";
					$l_first = 0;
				}
				print OUT "\\item ".$g_class[$l_class_c]->{$E_BASE_CLASSES}[$i]->{$E_NAME}."\n";
			}
		}
		if(!$l_first)
		{
			print OUT "\\end{itemize}\n";
		}
		$l_first = 1;
		
		for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_BASE_CLASSES}}; ++$i)
		{
			if( $g_class[$l_class_c]->{$E_BASE_CLASSES}[$i]->{$E_SCOPE} == 0 )
			{
				if($l_first)
				{
					print OUT "\\item []Privát ősosztályok:\n";
					print OUT "\\begin{itemize}\n";
					$l_first = 0;
				}
				print OUT "\\item ".$g_class[$l_class_c]->{$E_BASE_CLASSES}[$i]->{$E_NAME}."\n";
			}
		}
		if(!$l_first)
		{
			print OUT "\\end{itemize}\n";
		}
		$l_first = 1;
		
		print OUT "\\end{enumerate}\n";
		print OUT "\n";
	}
}

sub write_short_members_tex_p
{
	my $l_first = 1;
	my $l_class_c = $_[0];
	if(@{$g_class[$l_class_c]->{$E_MEMBERS}} > 0)
	{
		print OUT "\\textbf{Az osztály adattagjai:} \n";
		print OUT "\\begin{enumerate}\n";
		for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_MEMBERS}}; ++$i)
		{		
			if(!put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME}))
			{
				next;
			}
			if( $g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_SCOPE} == 2 )
			{
				if($l_first)
				{
					print OUT "\\item[Publikus] adattagok:\n";
					print OUT "\\begin{itemize}\n";
					$l_first = 0;
				}
				print OUT "\\item ".put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME})."\n";
			}
		}
		if(!$l_first)
		{
			print OUT "\\end{itemize}\n";
		}
		$l_first = 1;
		
		
		for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_MEMBERS}}; ++$i)
		{
			if(!put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME}))
			{
				next;
			}
			if( $g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_SCOPE} == 1 )
			{
				if($l_first)
				{
					print OUT "\\item[Védett] adattagok:\n";
					print OUT "\\begin{itemize}\n";
					$l_first = 0;
				}
				print OUT "\\item ".put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME})."\n";
			}
		}
		if(!$l_first)
		{
			print OUT "\\end{itemize}\n";
		}
		$l_first = 1;
		
		for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_MEMBERS}}; ++$i)
		{
			if(!put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME}))
			{
				next;
			}
			if( $g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_SCOPE} == 0 )
			{
				if($l_first)
				{
					print OUT "\\item[Privát] adattagok:\n";
					print OUT "\\begin{itemize}\n";
					$l_first = 0;
				}
				print OUT "\\item ".put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME})."\n";
			}
		}
		if(!$l_first)
		{
			print OUT "\\end{itemize}\n";
		}
		$l_first = 1;
		print OUT "\\end{enumerate}\n";
	}
	else
	{
		print OUT "\\textbf{Az osztálynak nincsennek adattagjai}\\\\\n";
	}
}

sub write_short_functions_tex_p
{
	my $l_class_c = $_[0];
	my $l_first = 1;
	if( @{$g_class[$l_class_c]->{$E_FUNCTIONS}} > 0)
	{
		print OUT "\n";
		print OUT "\\textbf{Az osztály függvényei:} \n";
		print OUT "\\begin{enumerate}\n";
		for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_FUNCTIONS}}; ++$i)
		{
			if(!put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME}))
			{
				next;
			}
			if( $g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_SCOPE} == 2 )
			{
				if($l_first)
				{
					print OUT "\\item[Publikus] függvények:\n";
					print OUT "\\begin{itemize}\n";
					$l_first = 0;
				}
				print OUT "\\item ".chop_last_lf_p(desc_2_tex_format(put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME})))."\n";
				print "write function: ".$g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME} if($g_debug);
			}
		}
		if(!$l_first)
		{
			print OUT "\\end{itemize}\n";
		}
		$l_first = 1;
		
		
		for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_FUNCTIONS}}; ++$i)
		{
			if(!put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME}))
			{
				next;
			}
			if( $g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_SCOPE} == 1 )
			{
				if($l_first)
				{
					print OUT "\\item[Védett] függvények:\n";
					print OUT "\\begin{itemize}\n";
					$l_first = 0;
				}
				print OUT "\\item ".chop_last_lf_p(desc_2_tex_format(put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME})))."\n";
				print "write function: ".desc_2_tex_format(put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME})) if($g_debug);
			}
		}
		if(!$l_first)
		{
			print OUT "\\end{itemize}\n";
		}
		$l_first = 1;
		
		for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_FUNCTIONS}}; ++$i)
		{	
			if(!put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME}))
			{
				next;
			}
			if( $g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_SCOPE} == 0 )
			{
				if($l_first)
				{
					print OUT "\\item[Privát] függvények:\n";
					print OUT "\\begin{itemize}\n";
					$l_first = 0;
				}
				print OUT "\\item ".chop_last_lf_p(desc_2_tex_format(put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME})))."\n";
				print "write function: ".$g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME} if($g_debug);
			}
		}
		if(!$l_first)
		{
			print OUT "\\end{itemize}\n";
		}
		$l_first = 1;
		
		print OUT "\\end{enumerate}\n";
	}
}


sub write_members_tex_p
{
	if(@{$g_class[$l_class_c]->{$E_MEMBERS}} > 0)
	{
		print "member count: ".@{$g_class[$l_class_c]->{$E_MEMBERS}}."\n" if($g_debug);
		my $l_class_c = $_[0];
		my $l_first = 1;
		print OUT "\\subsubsection{Adattagok} \n";
		for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_MEMBERS}}; ++$i)
		{		
			if(!put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME}))
			{
				next;
			}
			if( $g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_SCOPE} == 2 )
			{
				if($l_first)
				{
					print OUT "\\paragraph{Publikus adattagok}\n";
					print OUT "\\begin{itemize}\n";
					$l_first = 0;
				}
				print OUT "\\item ".put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME})."\\\\\n";
				print OUT "\\textbf{leírás:} ".put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_DESC})."\n";
			}
		}
		if(!$l_first)
		{
			print OUT "\\end{itemize}\n";
		}
		$l_first = 1;
		
		
		for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_MEMBERS}}; ++$i)
		{
			if(!put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME}))
			{
				next;
			}
			if( $g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_SCOPE} == 1 )
			{
				if($l_first)
				{
					print OUT "\\paragraph{Védett adattagok}\n";
					print OUT "\\begin{itemize}\n";
					$l_first = 0;
				}
				print OUT "\\item ".put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME})."\\\\\n";
				print OUT "\\textbf{leírás:} ".put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_DESC})."\n";
			}
		}
		if(!$l_first)
		{
			print OUT "\\end{itemize}\n";
		}
		$l_first = 1;
		
		for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_MEMBERS}}; ++$i)
		{
			if(!put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME}))
			{
				next;
			}
			if( $g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_SCOPE} == 0 )
			{
				if($l_first)
				{
					print OUT "\\paragraph{Privát adattagok}\n";
					print OUT "\\begin{itemize}\n";
					$l_first = 0;
				}
				print OUT "\\item ".put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_NAME})."\\\\\n";
			#	print OUT "\\index{Class ".put_escape_chars_p(last_word_p($g_class[$l_class_c]->{$E_NAME})."!".$g_class[0]->{$E_MEMBERS}[$i]->{$E_NAME})."}\n";
				print OUT "\\textbf{leírás:} ".put_escape_chars_p($g_class[$l_class_c]->{$E_MEMBERS}[$i]->{$E_DESC})."\n";
			}
		}
		if(!$l_first)
		{
			print OUT "\\end{itemize}\n";
		}
		$l_first = 1;
	}
}

sub write_functions_tex_p
{
	my $l_class_c = $_[0];
	my $l_first = 1;
	print OUT "\n";
	print OUT "\\subsubsection{Függvények:} \n";
	for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_FUNCTIONS}}; ++$i)
	{		
		if(!put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME}) || $g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_SIMPLE})
		{
			print "empty or simple: ".$g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME}."\n" if($g_debug);
			next;
		}
		if( $g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_SCOPE} == 2 )
		{
			if($l_first)
			{
				print OUT "\\paragraph{Publikus függvények}\n";
				$l_first = 0;
			}
			write_function_details_p($i, $l_class_c)
		}
	}
	$l_first = 1;
	
	
	for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_FUNCTIONS}}; ++$i)
	{
		if(!put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME}) || $g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_SIMPLE})
		{
			next;
		}
		if( $g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_SCOPE} == 1 )
		{
			if($l_first)
			{
				print OUT "\\paragraph{Védett függvények}\n";
				$l_first = 0;
			}
			write_function_details_p($i, $l_class_c);
		}
	}
	$l_first = 1;
	
	for(my $i = 0; $i < @{$g_class[$l_class_c]->{$E_FUNCTIONS}}; ++$i)
	{
		if(!put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_NAME}) || $g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_SIMPLE})
		{
			next;
		}
		if( $g_class[$l_class_c]->{$E_FUNCTIONS}[$i]->{$E_SCOPE} == 0 )
		{
			if($l_first)
			{
				print OUT "\\paragraph{Privát függvények}\n";
				$l_first = 0;
			}
			write_function_details_p($i, $l_class_c);
		}
	}
	$l_first = 1;
	
}

sub write_function_details_p
{
	my $p_id = $_[0];
	my $l_class_c = $_[1];
	my $l_exists_param = 0;
	my $l_exists_throw = 0;
	print OUT "\\subparagraph{function} ".desc_2_tex_format(put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_NAME}));
	#print OUT "\\index{Class ".put_escape_chars_p(last_word_p($g_class[$l_class_c]->{$E_NAME})."!".$g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_NAME})."}\n";
	print OUT "\\textbf{Leírás:} \\\\\n";
	print OUT chop_last_lf_p(desc_2_tex_format(put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_DESC})))."\n";
	
	if(defined $g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_PARAMS})
	{
		$l_exists_param = 1;
		print OUT "\\\\\n\\textbf{Paraméterek:}\n";
		print OUT "\\begin{itemize} \n";
		for(my $j = 0; $j < @{$g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_PARAMS}}; ++$j)
		{
			print OUT "\\item ".put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_PARAMS}[$j]->{$E_NAME}).":\\\\\n";
			print OUT put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_PARAMS}[$j]->{$E_DESC})."\n";
		}
		print OUT "\\end{itemize} \n";
	}
	if(defined $g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_THROW})
	{
		if(!$l_exists_param)
		{
			print OUT "\\\\\n"
		}
		$l_exists_throw = 1;
		print OUT "\\textbf{Kivételek:} \n";
		print OUT "\\begin{itemize} \n";
		for(my $j = 0; $j < @{$g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_THROW}}; ++$j)
		{
			print OUT "\\item ".put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_THROW}[$j]->{$E_NAME}).":\\\\\n";
			print OUT put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_THROW}[$j]->{$E_DESC})."\n";
		}
		print OUT "\\end{itemize} \n";
	}
	if(defined $g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_RETURN_VAL})
	{
		if(!$l_exists_param && !$l_exists_throw)
		{
			print OUT "\\\\\n"
		}
		print OUT "\\textbf{Visszatérési érték:}\\\\\n";
		print OUT put_escape_chars_p($g_class[$l_class_c]->{$E_FUNCTIONS}[$p_id]->{$E_RETURN_VAL})."\n";
	}
}

sub desc_2_tex_format
{
	my $p_desc = $_[0];
	my @l_tmp = split( /\n/, $p_desc);
	my $l_ret = "";
	foreach my $l_line(@l_tmp)
	{
		if($l_line !~ /}\s*$/)
		{
			if($l_line !~ /\\\\item/)
			{
				$l_ret.=$l_line."\\\\\n";
			}
			else
			{
				$l_ret.=$l_line."\n";
			}
		}
		else
		{
			$l_ret.=$l_line."\n";
		}
	}
	return $l_ret;
}
sub chop_last_lf_p
{
	my $p_str = $_[0];
	my @l_tmp = split(/\n/,$p_str);
	my $l_last_line = "";
	my $l_ret ="";
	for(my $i = 0; $i < @l_tmp - 1; ++$i)
	{
		$l_ret .= $l_tmp[$i]."\n";
	}
	$l_last_line = $l_tmp[@l_tmp-1];
	$l_last_line =~ s/\\\\//;
	$l_ret .= $l_last_line;
	return $l_ret;
}

sub put_escape_chars_p
{
	my $p_str = $_[0];
	my @l_t = split (/\n/,$p_str);
	my $l_ret = "";
	foreach my $l_line(@l_t)
	{
		my @l_tmp = split (/\s/,$l_line);
		foreach my $l_word (@l_tmp)
		{
			$l_word =~ s/(.*)&(.*)/$1\\&$2/;
			$l_word =~ s/(.*)_(.*)/$1\\_$2/;
			if($l_word =~ /<</)
			{
				$l_word =~ s/(.*)<<(.*)/$1\$\\ll\$$2/;
			}
			else
			{
				$l_word =~ s/(.*)<(.*)/$1\$<\$$2/;
			}
			if($l_word =~ />>/)
			{
				$l_word =~ s/(.*)>>(.*)/$1\$\\gg\$$2/;
			}
			else
			{
				$l_word =~ s/(.*)>(.*)/$1\$>\$$2/;
			}
			$l_ret = $l_ret.$l_word." ";
		}
		$l_ret .="\n";
	}
	return $l_ret;
}
