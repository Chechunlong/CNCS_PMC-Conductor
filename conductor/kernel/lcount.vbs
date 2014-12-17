'
' Count the lines of .c/.cpp/.h files under current directory, recursely
' by J.Hunter, 10/05/2001
' 一个小东西，把内容另存为一个Visual Basic脚本文件例如lcount.vbs
' 这个脚本文件运行时查找当前目录下的c语言源文件（包括*.c,*.cpp,*.h）并统计行数
' 并把统计结果自动存入lcount.log日志文件中。
' 无聊或者丧失斗志的时候运行一下这个程序，应该能感觉好一些（wokao！我写了这么多程序呢)
' 运行方式：在资源管理器里双击 lcount.vbs,或在命令行里：cscript lcount.vbs
'
'

dim ident
dim c_lines,c_files,cpp_lines,cpp_files,h_files,h_lines,i_folders,i_Files
dim pas_files,pas_lines
dim root
Dim debug_mode

main

function ident_string
    ident_string=""
    for i=1 to ident
         ident_string=ident_string & "    "
    next
end function

function count_lines_of_file(fl)
    set file=root.opentextfile(fl.path)
    if file is nothing then exit function
    while not file.atendofstream
        file.readline
        count_lines_of_file=count_lines_of_file+1
    wend
end function

sub deal_with_file(fl)
   If debug_mode<>0 Then
       wscript.echo ident_string & "Processing file " & fl.name
   End If
   if ucase(right(fl.name,4)) = ".CPP" then
       cpp_files=cpp_files+1
       cpp_lines=cpp_lines+count_lines_of_file(fl)
   End If
   If ucase(right(fl.name,2)) = ".C" then
       c_files=c_files+1
       c_lines=c_lines+count_lines_of_file(fl)
   End if
   If ucase(right(fl.name,2)) = ".H" then 
       h_files=h_files+1
       h_lines=h_lines+count_lines_of_file(fl)
   end If
   If ucase(right(fl.name,4)) = ".PAS" then 
       pas_files=pas_files+1
       pas_lines=pas_lines+count_lines_of_file(fl)
   end If
end sub

sub deal_with_folder(fd)
   If debug_mode<>0 Then
       wscript.echo ident_string & "Entering folder " & fd.name
   End if
   ident=ident+1
   i_folders=i_folders+1
   for each subfd in fd.subfolders
      deal_with_folder subfd
   next
   for each fl in fd.files
      i_files=i_files+1
      deal_with_file fl
   next
   ident=ident-1
   If debug_mode<>0 Then
       wscript.echo ident_string & "Leaving folder " & fd.name
   End if
end sub

sub main
   'On Error Resume Next
   c_lines=0
   c_files=0
   cpp_lines=0
   cpp_files=0
   h_files=0
   h_lines=0
   i_folders=0
   i_Files=0
   pas_files=0
   pas_lines=0

   set root=createobject("scripting.filesystemobject")
   set fd=root.getfolder(".")
   Set log_file=root.opentextfile("lcount.log",8,true)
   If log_file is nothing Then
       wscript.echo "Warning : Error opening log file."
   End If

   result=""
   
   deal_with_folder fd   
   
   result=result & vbcrlf & i_folders & " Folders"
   result=result & vbcrlf & i_files & " Files"
   result=result & vbcrlf & cpp_lines & " lines in " & cpp_files & " *.cpp files"
   result=result & vbcrlf & c_lines & " lines in " & c_files & " *.c files"
   result=result & vbcrlf & h_lines & " lines in " & h_files & " *.h files"
   result=result & vbcrlf & pas_lines & " lines in " & pas_files & " *.pas files"
   result=result & vbcrlf & "Total " & cpp_lines+c_lines+h_lines & " lines"
   result=result & vbcrlf & "look into lcount.log for the logging result."

   wscript.echo result
   
   If not log_file is nothing Then
       log_file.writeline "--------------------------------------------"
       log_file.writeline "      Log created on " & Now
       log_file.writeline "      by J.Hunter's logging utility, 10/05/2001"
       log_file.writeline "      Current directory is " & fd.path
       log_file.writeline i_folders & " Folders"
       log_file.writeline i_files & " Files"
       log_file.writeline cpp_lines & " lines in " & cpp_files & " *.cpp files"
       log_file.writeline c_lines & " lines in " & c_files & " *.c files"
       log_file.writeline h_lines & " lines in " & h_files & " *.h files"
       log_file.writeline pas_lines & " lines in " & pas_files & " *.pas files"
       log_file.writeline "Total " & cpp_lines+c_lines+h_lines+pas_files & " lines"
       log_file.close
   End If

   set fd=nothing
   set root=nothing
end sub