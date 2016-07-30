#include <stdio.h>
#include <string.h>

static int frameCnt[] = 
{
	3,
	1,
	1,
	1,
	1
};

int levels = 0;

void
RaiseLevel(void){
	levels++;
}

void
LowerLevel(void){
	levels--;
}

void
NewLine(FILE *f){
	for(int i = 0; i < levels; i++)
		fprintf(f, "\t");
}


void
showHelp(const char *name) {
			printf("%s : \n", name);
			printf("\t-labg filename\n");
			printf("\t-startimg filename\n");
			printf("\t-style [a1 a2 a3 a4 a5]\n");
}

int main(int argc, char *argv[]) {

	if(argc == 1) {
		showHelp(argv[0]);
		return 0;
	}

	for(int i = 1; i < argc; i++) {
		const char *arg = argv[i];

		if(strcmp(arg, "-help") == 0)
		{
			showHelp(argv[0]);
			return 0;
		}
	}

	int la_bg_arg_i = -1;
	int start_img_arg_i = -1;
	int style_arg_i = -1;
	int style_num = -1;

	for(int i = 1; i < argc; i++) {
		const char *arg = argv[i];

		if(strcmp(arg, "-labg") == 0) {
			la_bg_arg_i = ++i;
		}else if(strcmp(arg, "-startimg") == 0) {
			start_img_arg_i = ++i;
		}else if(strcmp(arg, "-style") == 0) {
			style_arg_i = ++i;
		}
	}

	const char *la_bg_img_path = "";
	if(la_bg_arg_i != -1)la_bg_img_path = argv[la_bg_arg_i];

	const char *start_img_path = "";
	if(start_img_arg_i != -1)start_img_path = argv[start_img_arg_i];

	const char *style_name = "a1";
	if(style_arg_i != -1)style_name = argv[style_arg_i];



	if(strlen(style_name) != 2 || ((style_name[0] != 'a') | (style_name[1] < '1' || style_name[1] > '5')))
	{
		fprintf(stderr, "Invalid style specified, valid values are a1, a2, a3, a4, a5");
		return -1;
	}

	style_num = style_name[1] - '1';

	//Now generate the xml
	FILE *f = fopen("template.xml", "w");
	if(f != NULL) {

		fprintf(f, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\n");
		fprintf(f, "<livearea style=\"%s\" format-ver=\"01.00\" content-rev=\"1\">\n\t", style_name);
		
		RaiseLevel();
		NewLine(f);
		fprintf(f, "<livearea-background>\n");
		

		RaiseLevel();
		NewLine(f);
		fprintf(f, "<image>%s</image>\n", la_bg_img_path);
		LowerLevel();
		
		NewLine(f);
		fprintf(f, "</livearea-background>\n");

		NewLine(f);
		fprintf(f, "<gate>\n");

		RaiseLevel();
		NewLine(f);
		fprintf(f, "<startup-image>%s</startup-image>", start_img_path);
		LowerLevel();
		
		NewLine(f);
		fprintf(f, "</gate>\n");
 
		for(int i = 0; i < frameCnt[style_num]; i++) {

			NewLine(f);
			fprintf(f, "<frame id=\"frame%d\">\n", i + 1);

			RaiseLevel();
			NewLine(f);
			fprintf(f, "<liveitem>\n");
			RaiseLevel();
			NewLine(f);
			fprintf(f, "<target>\n");
			NewLine(f);
			fprintf(f, "</target>\n");
			NewLine(f);
			fprintf(f, "<background>\n");
			NewLine(f);
			fprintf(f, "</background>\n");
			NewLine(f);
			fprintf(f, "<image>\n");
			NewLine(f);
			fprintf(f, "</image>\n");
			NewLine(f);
			fprintf(f, "<text>\n");
			NewLine(f);
			fprintf(f, "</text>\n");
			LowerLevel();
			NewLine(f);
			fprintf(f, "</liveitem>\n");

			LowerLevel();
			NewLine(f);
			fprintf(f, "</frame>\n");
		}

		LowerLevel();
		NewLine(f);
		fprintf(f, "</livearea>\n");
		fclose(f);
	}else{
		fprintf(stderr, "Error: Failed to open file for writing");
		return -1;
	} 

}