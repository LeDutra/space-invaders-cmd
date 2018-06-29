#include "header.c" // Cabe�alho com todas os includes e defines
#include "libraries/custom_bibl.h" // Biblioteca customizada por euzinho (Leo) que cont�m umas fun��es de cores e coisas E S T � T I C A S
#include "prototypes.c" // Prot�tipos pra n�o ficar dando warning que a fun��o � implicita

int main()
{

    int tempo, deltaTempo=0;
    int nave[3]= {navePOSX,navePOSY,naveDeltaVx};
    int tiro[3]= {tiroPOSX,tiroPOSY,tiroStatus};
    int flag_quit = 1;
    int flag_morte = 1;
    int flag_pause = 0;

    tela_inicial();
    do
    {
        anima_barra(nave);
        tempo=time(NULL);
        while(deltaTempo<40&&flag_quit&&flag_morte)
        {
            if(kbhit())
                leitura_teclado(nave,tiro, &flag_quit, &flag_pause);
            else
                movimenta(nave,0);
//            system("cls");
            atirar(nave,tiro);
            posiciona_nave(nave,0);
            deltaTempo=time(NULL)-tempo;
            ajusta_energia(deltaTempo);
            imprime_tela(deltaTempo);
            if(flag_pause)
            {
                PlaySoundA(TEXT("sounds/coin.wav"), NULL, SND_ASYNC);
                gotoxy(18, 12);
                colorfn();
                printf("Pausado! Pressione qualquer tecla para voltar");
                gotoxy(22, 13);
                printf("ou pressione ESC para sair do jogo");
                while(!kbhit())
                {
                    Sleep(1000);
                    tempo++;
                }
                PlaySoundA(TEXT("sounds/coin.wav"), NULL, SND_SYNC);
                flag_pause=0;
            }
            if(deltaTempo == 35 || deltaTempo == 37 || deltaTempo == 39)
                PlaySoundA(TEXT("sounds/alarm.wav"), NULL, SND_ASYNC);
            Sleep(17);
        }
        if(deltaTempo>=40)
            PlaySoundA(TEXT("sounds/energy.wav"), NULL, SND_ASYNC);
        else if(flag_morte)
            PlaySoundA(TEXT("sounds/expl.wav"), NULL, SND_ASYNC);
        Sleep(2000);
        nave[0]= navePOSX;
        nave[1]= navePOSY;
        nave[2]= naveDeltaVx;
        tiro[0]= tiroPOSX;
        tiro[1]= tiroPOSY;
        tiro[2]= tiroStatus;
        posiciona_nave(nave,0);
        Sleep(300);
        system("cls");
        limpa_barra();
        deltaTempo = 0;
        flag_morte = 1;
    }
    while(diminui_vida()&&flag_quit);
    if(flag_quit)
        tela_game_over();
    else
        printf("\nSaindo do jogo!");
    return 0;
}
