
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <string.h>
#include <string.h>
#include <ctype.h>  
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>  
///////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
///////////////////////////////////////////////////////////////////
#include "libc-str.c"
#include "libc-bin.c"



int sectionnbr    = 0;
int subsectionnbr = 0;

void filenew( char *fileout)
{
    FILE *fp5;
    fp5 = fopen( fileout , "wb+");
    fclose( fp5 );
}





void fileclosertf( char *fileout)
{
    FILE *fp5;
     // close the rtf
     fp5 = fopen( fileout , "ab+"); 
	 fputs( "\\par }\n", fp5 );
     fclose( fp5 );
}





///////////////////////////////////////////////////////////////////
void filerawcat(  char *fileout, char *filein )
{
  int fetchi;
  FILE *fp5;
  FILE *fp6;
  char fetchline[PATH_MAX];
  char fetchlinetmp[PATH_MAX];
  /////////////////////////////////////////////////
  if ( fexist( filein ) == 1 )
  {
    fp5 = fopen( fileout , "ab+");
    fp6 = fopen( filein , "rb");
    while( !feof(fp6) ) 
    {
          fgets(fetchlinetmp, PATH_MAX, fp6); 
          strncpy( fetchline, "" , PATH_MAX );
          for( fetchi = 0 ; ( fetchi <= strlen( fetchlinetmp ) ); fetchi++ )
            if ( fetchlinetmp[ fetchi ] != '\n' )
              fetchline[fetchi]=fetchlinetmp[fetchi];

         if ( !feof(fp6) )
         {
 	      fputs( fetchline , fp5 );
  	      fputs( "\n", fp5 );
	 }
     }
     fclose( fp5 );
     fclose( fp6 );
   }
}





///////////////////////////////////////////////////////////////////
void fileiex2rtf( int filemode , char *fileout, char *filein ){
  int fetchi;
  int i , j , k ; 
  FILE *fp5;
  FILE *fp6;
  char charo[PATH_MAX];
  char fetchline[PATH_MAX];
  char fetchlinetmp[PATH_MAX];
  int foundcode = 0;
  int foundlinefeed = 0;
  int commenton = 0;
  int fpreader = 1;


  /////////////////////////////////////////////////
  if ( fexist( filein ) == 1 )
  {
    fp5 = fopen( fileout , "ab+");
    fp6 = fopen( filein , "rb+");
    // while( !feof(fp6) ) 
    while ( ( !feof(fp6) ) &&  ( fpreader == 1 ) )
    {
          fgets(fetchlinetmp, PATH_MAX, fp6); 
          strncpy( fetchline, "" , PATH_MAX );
          foundcode = 0;

          for( fetchi = 0 ; ( fetchi <= strlen( fetchlinetmp ) ); fetchi++ )
            if ( fetchlinetmp[ fetchi ] != '\n' )
              fetchline[fetchi]=fetchlinetmp[fetchi];

         if ( ( !feof(fp6) ) &&  ( fpreader == 1 ) )
         {

            /////////////////////////////////////
            if ( foundcode == 0 )
            if ( fetchline[0] == '/' )
            if ( fetchline[1] == '*' )
            {
  	      commenton = 1;
            }

            if ( foundcode == 0 )
            if ( fetchline[0] == '*' )
            if ( fetchline[1] == '/' )
            {
  	      commenton = 0;
    	      foundcode = 1;
            }

            if ( commenton == 1 )
            {
    	      foundcode = 1;
            }
            /////////////////////////////////////
            /////////////////////////////////////

            if ( foundcode == 0 )
            if ( fetchline[0] == '/' )
            if ( fetchline[1] == '/' )
            {
  	        foundcode = 1;
  	        foundcode = 1;
            }

            if ( foundcode == 0 )
            if ( fetchline[0] == '$' )
            if ( fetchline[1] == 'b' )
            if ( fetchline[2] == 'r' )
            if ( fetchline[3] == 'e' )
            if ( fetchline[4] == 'a' )
            if ( fetchline[5] == 'k' )
            {
  	      fpreader = 0;
  	      foundcode = 1;
            }
            /////////////////////////////////////
            /////////////////////////////////////









/*
 \par {\i italic }
 \par {\cf6 This is red}
 \par {\cf2 This is blue}
 \par {\cf17 This is green}
*/

            // $linefeed
	    //////////////////////////////////
            if ( foundcode == 0 )
            if ( strcmp(fetchline, "" ) == 0 )
            {
              if ( foundlinefeed == 0 )
	      {
	         fputs( "\\par " , fp5 );
  	         fputs( "\n", fp5 );
                 foundlinefeed = 1;
	      }
	      else 
	      {
	      }
  	      foundcode = 1;
            }







      //////////////////// NO LINE FEED
      //////////////////// CORE
            // $green
            if ( foundcode == 0 )
            //if ( fetchline[0] == '$' )
            if (( fetchline[0] == '$' ) || ( fetchline[0] == '!' ))
            if ( fetchline[1] == 'g' )
            if ( fetchline[2] == 'r' )
            if ( fetchline[3] == 'e' )
            if ( fetchline[4] == 'e' )
            if ( fetchline[5] == 'n' )
            if ( fetchline[6] == ' ' )
            {
 	      fputs( "{\\cf17 " , fp5 );
 	      fputs( strcut( fetchline, 7, strlen(fetchline)-1) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }

            // $bold
            if ( foundcode == 0 )
            //if ( fetchline[0] == '$' )
            if (( fetchline[0] == '$' ) || ( fetchline[0] == '!' ))
            if ( fetchline[1] == 'b' )
            if ( fetchline[2] == 'o' )
            if ( fetchline[3] == 'l' )
            if ( fetchline[4] == 'd' )
            if ( fetchline[5] == ' ' )
            {
 	      fputs( "{\\b " , fp5 );
 	      fputs( strcut( fetchline, 6, strlen(fetchline)-1) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }



            // $ital 
            if ( foundcode == 0 )
            if (( fetchline[0] == '$' ) || ( fetchline[0] == '!' ))
            if ( fetchline[1] == 'i' )
            if ( fetchline[2] == 't' )
            if ( fetchline[3] == 'a' )
            if ( fetchline[4] == 'l' )
            if ( fetchline[5] == ' ' )
            {
 	      fputs( "{\\i " , fp5 );
 	      fputs( strcut( fetchline, 6, strlen(fetchline)-1) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }

            // $blue
            if ( foundcode == 0 )
            //if ( fetchline[0] == '$' )
            if (( fetchline[0] == '$' ) || ( fetchline[0] == '!' ))
            if ( fetchline[1] == 'b' )
            if ( fetchline[2] == 'l' )
            if ( fetchline[3] == 'u' )
            if ( fetchline[4] == 'e' )
            if ( fetchline[5] == ' ' )
            {
 	      fputs( "{\\cf2 " , fp5 );
 	      //fputs( strcut( fetchline, 6, strlen(fetchline)-1) , fp5 );
 	      fputs( strcut( fetchline, 6, strlen(fetchline)) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }

            // $red
            if ( foundcode == 0 )
            if (( fetchline[0] == '$' ) || ( fetchline[0] == '!' ))
            if ( fetchline[1] == 'r' )
            if ( fetchline[2] == 'e' )
            if ( fetchline[3] == 'd' )
            if ( fetchline[4] == ' ' )
            {
 	      fputs( "{\\cf6 " , fp5 );
 	      fputs( strcut( fetchline, 5, strlen(fetchline)-1) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }

    //////////////////////////////////////////////////////
    //////////////////////////////////////////////////////
    //////////////////////////////////////////////////////
    //////////////////////////////////////////////////////








            /// =======
            if ( foundcode == 0 )
            if ( fetchline[0] == '=' )
            if ( fetchline[1] == '=' )
            if ( fetchline[2] == '=' )
            if ( fetchline[3] == '=' )
            if ( fetchline[4] == '=' )
            if ( fetchline[5] == '=' )
            {
	       fputs( "\\par " , fp5 );
 	      fputs( fetchline , fp5 );
  	      fputs( "\n", fp5 );
	       fputs( "\\par " , fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }



            /// abstract
            if ( foundcode == 0 )
            if ( fetchline[0] == '>' )
            if ( fetchline[1] == ' ' )
            {
	       fputs( "\\par " , fp5 );
 	      fputs( "{\\b " , fp5 );
 	      fputs( strcut( fetchline, 2, strlen(fetchline)-1) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
	       fputs( "\\par " , fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }



            /// new line
            if ( foundcode == 0 )
            if ( fetchline[0] == '$' )
            if ( fetchline[1] == 'l' )
            if ( fetchline[2] == 'n' )
            if ( fetchline[3] == ' ' )
            {
	       fputs( "\\par " , fp5 );
 	      fputs( strcut( fetchline, 4, strlen(fetchline)-1) , fp5 );
  	      fputs( "\n", fp5 );
	       fputs( "\\par " , fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }

            // $im or new item
            if ( foundcode == 0 )
            if ( fetchline[0] == '*' )
            if ( fetchline[1] == ' ' )
            {
 	      fputs( "* " , fp5 );
 	      fputs( strcut( fetchline, 2, strlen(fetchline)-1) , fp5 );
  	      fputs( "\n", fp5 );
	       fputs( "\\par " , fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }


            // $im or new item
            if ( foundcode == 0 )
            if ( fetchline[0] == '-' )
            if ( fetchline[1] == ' ' )
            {
 	      fputs( "- " , fp5 );
 	      fputs( strcut( fetchline, 2, strlen(fetchline)-1) , fp5 );
  	      fputs( "\n", fp5 );
	       fputs( "\\par " , fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }

            // $im or new item
            if ( foundcode == 0 )
            if ( fetchline[0] == '$' )
            if ( fetchline[1] == 'i' )
            if ( fetchline[2] == 'm' )
            if ( fetchline[3] == ' ' )
            {
	       fputs( "\\par " , fp5 );
 	      fputs( "- " , fp5 );
 	      fputs( strcut( fetchline, 4, strlen(fetchline)-1) , fp5 );
  	      fputs( "\n", fp5 );
	       fputs( "\\par " , fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }



            // reader comments $com
            if ( foundcode == 0 )
            //if ( fetchline[0] == '$' )
            if (( fetchline[0] == '$' ) || ( fetchline[0] == '!' ))
            if ( fetchline[1] == 'c' )
            if ( fetchline[2] == 'o' )
            if ( fetchline[3] == 'm' )
            if ( fetchline[4] == ' ' )
            {
 	      fputs( "{\\cf6  [" , fp5 );
 	      fputs( strcut( fetchline, 5, strlen(fetchline)-1) , fp5 );
  	      fputs( "]} ", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }

            // reader par / new line / new paragraph
            if ( foundcode == 0 )
            //if ( strcmp( fetchline , "$par" ) == 0 )
            if (( fetchline[0] == '$' ) || ( fetchline[0] == '!' ))
            {
	       fputs( "\\par " , fp5 );
  	      fputs( "\n", fp5 );
              foundlinefeed = 0;
  	      foundcode = 1;
  	      foundcode = 1;
            }


            // $subsection 
            if ( foundcode == 0 )
            if ( fetchline[0] == '#' )
            if ( fetchline[1] == '#' )
            if ( fetchline[2] == ' ' )
            {
	       fputs( "\\par " , fp5 );
 	      fputs( "{\\b " , fp5 );
              j = snprintf( charo, 25 , "%d.%d. ", sectionnbr, ++subsectionnbr );
 	      fputs( charo, fp5 );
 	      //fputs( strcut( fetchline, 3, strlen(fetchline)-1) , fp5 );
 	      fputs( strcut( fetchline, 3, strlen(fetchline)) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
	       fputs( "\\par " , fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }

            // $section 
            if ( foundcode == 0 )
            if ( fetchline[0] == '#' )
            if ( fetchline[1] == ' ' )
            {
	       fputs( "\\par " , fp5 );
 	      fputs( "{\\b " , fp5 );
              j = snprintf( charo, 5 , "%d. ", ++sectionnbr );
 	      fputs( charo, fp5 );
 	      fputs( strcut( fetchline, 2, strlen(fetchline)-1) , fp5 );
  	      fputs( "}", fp5 );
  	      fputs( "\n", fp5 );
	       fputs( "\\par " , fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
              subsectionnbr = 0;
            }




  	    if ( foundcode == 0 )
  	    if ( strcmp( fetchline, "" ) != 0 )
            {
 	      fputs( fetchline , fp5 );
  	      fputs( "\\par", fp5 );
  	      fputs( "\n", fp5 );
  	      foundcode = 1;
              foundlinefeed = 0;
            }

	 }
     }
     fclose( fp5 );
     fclose( fp6 );

   }
}




 

int main()
{
    filenew(    "export.rtf" );
    filerawcat( "export.rtf" , "header.rtf" );
    fileiex2rtf( 1, "export.rtf" , "text.txt" );
    fileclosertf( "export.rtf" );
    return 0;
}

