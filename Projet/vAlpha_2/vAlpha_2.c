#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>

#define VIDE 0
#define MUR 1
#define CAISSE 2
#define JOUEUR 3
#define ARRIVE 4

#define largeur 400
#define hauteur 400

static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play

struct pos
{
	int x;
	int y;
};
typedef struct pos POS;

struct level
{
	int width;
	int height;
	int T[100][100];
	POS joueur;
};

typedef struct level LEVEL;

void affichelvl(SDL_Surface *ecran,LEVEL niveau);
LEVEL lecture_fichier();
void pause();
void jouer_musique();
void my_audio_callback(void *userdata, Uint8 *stream, int len);

main()
{
	SDL_Surface *ecran = NULL;

	TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    
    

    SDL_WM_SetCaption("Sokoban vAlpha2",NULL);

    ecran = SDL_SetVideoMode(largeur,hauteur,32,SDL_HWSURFACE);
	
	LEVEL lvl;
	
	lvl=lecture_fichier();
	
	affichelvl(ecran,lvl);
	
	jouer_musique();
	
	pause();
	
	exit(EXIT_SUCCESS);
}




void affichelvl(SDL_Surface *ecran,LEVEL niveau)
{
	SDL_Surface *vide = NULL;
	SDL_Surface *mur = NULL;
	SDL_Surface *caisse = NULL;
	SDL_Surface *joueur = NULL;
	SDL_Surface *arrive = NULL;

	vide = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	mur = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	caisse = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	joueur = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	
	SDL_FillRect(vide, NULL, SDL_MapRGB(ecran->format, 100, 247, 255));
	SDL_FillRect(mur, NULL, SDL_MapRGB(ecran->format, 142, 142, 142));
	SDL_FillRect(caisse, NULL, SDL_MapRGB(ecran->format, 237, 161, 55));
	SDL_FillRect(joueur, NULL, SDL_MapRGB(ecran->format, 58, 255, 77));
	SDL_FillRect(arrive, NULL, SDL_MapRGB(ecran->format, 228, 0, 8));
	
	SDL_Rect positionCase;
	
	int i,j;
	
	for(i=0;i<niveau.width;i++)
    {
		for(j=0;j<niveau.height;j++)
		{
			positionCase.x=i*(largeur/niveau.width);
			positionCase.y=j*(hauteur/niveau.height);
			
			switch(niveau.T[i][j])
			{
				case VIDE:
					SDL_BlitSurface(vide,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case MUR:
					SDL_BlitSurface(mur,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case CAISSE:
					SDL_BlitSurface(caisse,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case JOUEUR:
					SDL_BlitSurface(joueur,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case ARRIVE:
					SDL_BlitSurface(arrive,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				default :
					printf("you forgot to blit a surface");
					break;
			}
		}
	}
	
	
	SDL_FreeSurface(vide);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(joueur);
	SDL_FreeSurface(mur);
	SDL_FreeSurface(arrive);
}


LEVEL lecture_fichier()
{
	FILE* fichier_lvl = fopen("fichier_niveaux.txt","r");
	if(fichier_lvl == NULL) exit(-1);
	
	LEVEL niveau;
	int i,j;
	
	fscanf(fichier_lvl, "%d %d\n", &niveau.width, &niveau.height);
	
	for(j=0;j<niveau.height+1;j++)
	{
		for(i=0;i<niveau.width+1;i++)
		{
			switch(fgetc(fichier_lvl))
			{
				case ' ':
					niveau.T[i][j]=VIDE;
					break;
				case '#':
					niveau.T[i][j]=MUR;
					break;
				case '&':
					niveau.T[i][j]=CAISSE;
					break;
				case '@':
					niveau.T[i][j]=JOUEUR;
					break;
				case '.':
					niveau.T[i][j]=ARRIVE;
					break;
			}
		}
	}
	
	fclose(fichier_lvl);
	return niveau;
}


void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}


void jouer_musique()
{
	// local variables
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music
	
	
	/* Load the WAV */
	// the specs, length and buffer of our wav are filled
	SDL_LoadWAV("01 Hammerwatch.wav", &wav_spec, &wav_buffer, &wav_length);

	
	
	// set the callback function
	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;
	// set our global static variables
	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length
	
	/* Open the audio device */
	if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
	  fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
	  exit(-1);
	}
	
	/* Start playing */
	SDL_PauseAudio(0);

	// wait until we're don't playing
	while ( audio_len > 0 ) {
		SDL_Delay(100); 
	}
	
	// shut everything down
	SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);
	
}

void my_audio_callback(void *userdata, Uint8 *stream, int len) {
	
	if (audio_len ==0)
		return;
	
	len = ( len > audio_len ? audio_len : len );
	//SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another
	
	audio_pos += len;
	audio_len -= len;
}

/*
#define MUS_PATH "Roland-GR-1-Trumpet-C5.wav"

// prototype for our audio callback
// see the implementation for more information
void my_audio_callback(void *userdata, Uint8 *stream, int len);

int main(int argc, char* argv[]){
	
	// local variables
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music
	
	
	// Load the WAV 
	// the specs, length and buffer of our wav are filled
	if( SDL_LoadWAV(MUS_PATH, &wav_spec, &wav_buffer, &wav_length) == NULL ){
	  return 1;
	}
	// set the callback function
	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;
	// set our global static variables
	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length
	
	// Open the audio device 
	if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
	  fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
	  exit(-1);
	}
	
	// Start playing 
	SDL_PauseAudio(0);

	// wait until we're don't playing
	while ( audio_len > 0 ) {
		SDL_Delay(100); 
	}
	
	// shut everything down
	SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);

}

// audio callback function
// here you have to copy the data of your audio buffer into the
// requesting audio buffer (stream)
// you should only copy as much as the requested length (len)
*/






















