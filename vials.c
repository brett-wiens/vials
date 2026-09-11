#include <stdio.h>
#include <string.h>

const char N_vials = 16;
const char N_slots = 4;
void recurse(char* vials);
void PrintVials(char* vials);

char IsSolved( char* vials ) {
	for( char i=0; i<N_vials; i++ ) {
		char colour = vials[i*N_slots];
		for( char j=1; j<N_slots; j++ ) if( vials[i*N_slots+j]!=colour ) return 0; }
	return 1; }

char CanPour( char* src, char* dest, char* ptr_dest_space, char* ptr_src_colour, char* ptr_src_start, char* ptr_src_height ) { 
		// Find dest colour and space
		char dest_colour = 0;
		*ptr_dest_space = 0;
		while( *ptr_dest_space < 4 && dest[*ptr_dest_space] == 0 ) (*ptr_dest_space)++;
		if( *ptr_dest_space == 0 ) return 0;
		if( *ptr_dest_space < 4 ) dest_colour = dest[*ptr_dest_space];

		// Find source colour and height
		*ptr_src_colour = 0;
		*ptr_src_start = 0;
		while( *ptr_src_start < 4 && src[*ptr_src_start] == 0 ) (*ptr_src_start)++;
		if( *ptr_src_start >= 4 ) return 0;
		*ptr_src_colour = src[*ptr_src_start];
		if( dest_colour != 0 && dest_colour != *ptr_src_colour ) return 0;
		*ptr_src_height = 1;
		while( *ptr_src_start + *ptr_src_height < 4 && src[*ptr_src_start+*ptr_src_height] == *ptr_src_colour ) (*ptr_src_height)++;
		if( *ptr_dest_space < *ptr_src_height ) return 0;
		if( *ptr_dest_space == N_slots && *ptr_src_start+*ptr_src_height == N_slots ) return 0;
		return 1; }

void Pour( char* src, char* dest, char* ptr_dest_space, char* ptr_src_colour, char* ptr_src_start, char* ptr_src_height ) { 
	// Move it all over
	for( char i=0; i<*ptr_src_height; i++ ) {
		dest[*ptr_dest_space-1-i] = src[*ptr_src_start+*ptr_src_height-1-i];
		src[*ptr_src_start+*ptr_src_height-1-i] = 0; }}


// 1 = blue
// 2 = dark pink
// 3 = dark purmple
// 4 = aqua
// 5 = crimson
// 6 = light purple
// 7 = dark blue
// 8 = dark green
// 9 = dark grey
// 10 = orange
// 11 = light pink
// 12 = light green
// 13 = light blue
// 14 = white
int main() {
	char vials[] = { 1,2,3,4,
	                5,6,7,8,
	                6,3,8,5,
	                4,3,5,9,
	                0,0,0,0,
	                1,8,2,10,
	                9,2,2,11,
	                10,10,11,12,
	                9,11,12,13,
	                8,12,13,7,
	                11,10,13,14,
	                7,13,14,6,
	                4,12,14,4,
	                0,0,0,0,
	                14,7,5,1,
	                9,3,6,1 };
/*printf("Starting state: \n");
	PrintVials( vials );
int dest_space, src_colour, src_start, src_height;
int cp03 = CanPour( &vials[0*N_slots], &vials[3*N_slots], &dest_space, &src_colour, &src_start, &src_height );
int cp04 = CanPour( &vials[0*N_slots], &vials[4*N_slots], &dest_space, &src_colour, &src_start, &src_height );
printf("Canpour 0 3?: %d\nCanpour 0 4?: %d\n", cp03, cp04);
Pour( &vials[0*N_slots], &vials[4*N_slots], &dest_space, &src_colour, &src_start, &src_height );
PrintVials( vials );
CanPour( &vials[0*N_slots], &vials[13*N_slots], &dest_space, &src_colour, &src_start, &src_height );
Pour( &vials[0*N_slots], &vials[13*N_slots], &dest_space, &src_colour, &src_start, &src_height );
PrintVials( vials );*/
	recurse( vials );
	return 0; }
	
void PrintVials( char* vials ) {
	for( char i=0; i<N_vials; i++ ) {
        	for( char j=0; j<N_slots; j++ ) putc(vials[i*N_slots+j]+0x30,stdout);
                putc(' ',stdout); }
        putc('\n',stdout); }

void recurse( char* vials ) {
	char found_flag = 0;
	for( char i=0; i<N_vials; i++ ) for ( char j=0; j<N_vials; j++ ) {
		if( i==j ) continue;
		char dest_space, src_colour, src_start, src_height;
		if( CanPour( &vials[i*N_slots], &vials[j*N_slots], &dest_space, &src_colour, &src_start, &src_height ) ) {
//printf(" Canpour %d %d: ", i, j); PrintVials(vials);
			found_flag = 1;
			char newvials[N_vials*N_slots];
			memcpy( newvials, vials, sizeof(char)*N_vials*N_slots );
			Pour( &newvials[i*N_slots], &newvials[j*N_slots], &dest_space, &src_colour, &src_start, &src_height );
			recurse( newvials ); }}
	if( found_flag == 0 ) {
		PrintVials( vials ); }}

	
	
