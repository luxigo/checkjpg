#include <stdio.h>
#include <stdlib.h>

int jpeg_checkEndMarker(char *filename) {

  // read the two last bytes
  
  unsigned char buf[2];
  FILE *f=fopen(filename, "r");
  if (!f) {
    fprintf(stderr,"%s: open failed !\n",filename);
    return 1;
  }

  int ret=fseek(f, -2, SEEK_END);
  if (ret<0) {
    fclose(f);
    fprintf(stderr,"%s: seek error !\n",filename);
    return 1;
  }

  int count=fread(buf, (size_t)1, (size_t)2, f);
  fclose(f);
  if (count!=2) {
    fprintf(stderr,"%s: read error !\n",filename);
    return 1;
  }

  // check whether the end marker is missing
  
  if (buf[0]!=0xff && buf[1]!=0xd9) {
    fprintf(stderr,"%s: invalid end marker !\n",filename);
    return 2;
  }

  return 0;
}

int main(int argc, char **argv) {

  const char *usage="%s <jpg_file> ...\n";
  int i;
  int ret=0;

  if (argc<2) {
    fprintf(stderr,usage,argv[0]);
    exit(1);
  }

  for (i=1; i<argc ; ++i) {
    ret|=jpeg_checkEndMarker(argv[i]);
  }

  // ret:
  // 1st bit to 1 == error occured
  // 2nd bit to 1 == invalid end marker
  return ret;
}
