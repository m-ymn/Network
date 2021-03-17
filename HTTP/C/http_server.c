

#include <stdio.h>
#include <winSock2.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library


#define SERVER_PORT  8899
#define SERVER_ADDR  "127.0.88.10" //"192.168.1.8"


const char intro[] =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html\r\n"
"Connection: Close\r\n\r\n"
"<html lang=\"en\"> <head> <meta charset=\"UTF-8\"/> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"/> <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\"/> <link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.5.0/css/all.css\" integrity=\"sha384-B4dIYHKNBt8Bc12p+WXckhzcICo0wtJAoU8YZTY5qE0Id1GSseTk6S+L3BlXeVIU\" crossorigin=\"anonymous\"/> <link rel=\"stylesheet\" href=\"css/main.css\"/> <title>Welcome to My Website</title> </head> <body id=\"bg-img\"> <header> <div class=\"menu-btn\"> <div class=\"btn-line\"></div><div class=\"btn-line\"></div><div class=\"btn-line\"></div></div><nav class=\"menu\"> <div class=\"menu-branding\"><div class=\"portrait\"></div></div><ul class=\"menu-nav\"> <li class=\"nav-item current\"> <a href=\"index.html\" class=\"nav-link\"> Home </a> </li><li class=\"nav-item\"> <a href=\"about.html\" class=\"nav-link\"> ABOUT ME </a> </li><li class=\"nav-item\"> <a href=\"work.html\" class=\"nav-link\"> MY WORK </a> </li><li class=\"nav-item\"> <a href=\"contact.html\" class=\"nav-link\"> DO NOT REACH ME </a> </li></ul> </nav> </header> <main id=\"home\"> <h1 class=\"lg-heading\"> Yameen <span class=\"text-secondary\">Kashu</span> </h1> <h2 class=\"sm-heading\"> Hello there ! </h2> <div class=\"icons\"> <a href=\"https://www.linkedin.com/in/yameen-kashu/\"> <i class=\"fab fa-linkedin fa-2x\"></i> </a> <a href=\"https://github.com/m-ymn\"> <i class=\"fab fa-github fa-2x\"></i> </a> </div></main> <script src=\"js/main.js\"></script> </body></html>" ;

const char stylesheet[] =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/css\r\n"
"Connection: Close\r\n\r\n"
".menu-btn{position: absolute; z-index: 3; right: 35px; top: 35px; cursor: pointer; transition: all 0.5s ease-out;}.menu-btn .btn-line{width: 28px; height: 3px; margin: 0 0 5px 0; background: #fff; transition: all 0.5s ease-out;}.menu-btn.close{transform: rotate(180deg);}.menu-btn.close .btn-line:nth-child(1){transform: rotate(45deg) translate(5px, 5px);}.menu-btn.close .btn-line:nth-child(2){opacity: 0;}.menu-btn.close .btn-line:nth-child(3){transform: rotate(-45deg) translate(7px, -6px);}.menu{position: fixed; top: 0; width: 100%; opacity: 0.9; visibility: hidden;}.menu.show{visibility: visible;}.menu-branding, .menu-nav{display: flex; flex-flow: column wrap; align-items: center; justify-content: center; float: left; width: 50%; height: 100vh; overflow: hidden;}.menu-nav{margin: 0; padding: 0; background: #373737; list-style: none; transform: translate3d(0, -100%, 0); transition: all 0.5s ease-out;}.menu-nav.show{transform: translate3d(0, 0, 0);}.menu-branding{background: #444; transform: translate3d(0, 100%, 0); transition: all 0.5s ease-out;}.menu-branding.show{transform: translate3d(0, 0, 0);}.menu-branding .portrait{width: 250px; height: 250px; background: url(\"../img/portrait.jpg\"); border-radius: 50%; border: solid 3px #eece1a;}.menu .nav-item{transform: translate3d(600px, 0, 0); transition: all 0.5s ease-out;}.menu .nav-item.show{transform: translate3d(0, 0, 0);}.menu .nav-item.current > a{color: #eece1a;}.menu .nav-link{display: inline-block; position: relative; font-size: 30px; text-transform: uppercase; padding: 1rem 0; font-weight: 300; color: #fff; text-decoration: none; transition: all 0.5s ease-out;}.menu .nav-link:hover{color: #eece1a;}.nav-item:nth-child(1){transition-delay: 0.1s;}.nav-item:nth-child(2){transition-delay: 0.2s;}.nav-item:nth-child(3){transition-delay: 0.3s;}.nav-item:nth-child(4){transition-delay: 0.4s;}*{box-sizing: border-box;}h1,h2,h3{margin: 0; font-weight: 400;}h1.lg-heading, h2.lg-heading, h3.lg-heading{font-size: 82px;}h1.sm-heading, h2.sm-heading, h3.sm-heading{margin-bottom: 2rem; padding: 0.2rem 1rem; background: rgba(73, 73, 73, 0.5);}a{color: #fff; text-decoration: none;}header{position: fixed; z-index: 2; width: 100%;}.text-secondary{color: #eece1a;}main{padding: 4rem; min-height: calc(100vh - 60px);}main .icons{margin-top: 1rem;}main .icons a{padding: 0.4rem;}main .icons a:hover{color: #eece1a; transition: all 0.5s ease-out;}main#home{overflow: hidden;}main#home h1{margin-top: 20vh;}.about-info{display: grid; grid-gap: 30px; grid-template-areas: \"bioimage bio bio\" \"job1 job2 job3\"; grid-template-columns: repeat(3, 1fr);}.about-info .about-skills{text-align: center; background: rgba(73, 73, 73, 0.5);}.about-info .about-skills .skills-list{color: #eece1a; list-style: none; padding: 0;}.about-info .bio-image{grid-area: bioimage; margin: auto; border-radius: 50%; border: #eece1a 3px solid;}.about-info .bio{grid-area: bio; font-size: 1.5rem;}.about-info .job-1{grid-area: job1;}.about-info .job-2{grid-area: job2;}.about-info .job-3{grid-area: job3;}.about-info .job{background: #515151; padding: 0.5rem; border-bottom: #eece1a 5px solid;}.projects{display: grid; grid-gap: 0.7rem; grid-template-columns: repeat(3, 1fr);}.projects img{width: 100%; border: 3px #fff solid;}.projects img:hover{opacity: 0.5; border-color: #eece1a; transition: all 0.5s ease-out;}.btn, .btn-dark, .btn-light{display: block; padding: 0.5rem 1rem; border: 0; margin-bottom: 0.3rem;}.btn:hover, .btn-dark:hover, .btn-light:hover{background: #eece1a; color: #000;}.btn-dark{background: black; color: #fff;}.btn-light{background: #c4c4c4; color: #333;}#main-footer{text-align: center; padding: 1rem; background: #2b2b2b; color: #fff; height: 60px;}@media screen and (min-width: 1171px){body{background: #444; color: #fff; height: 100%; margin: 0; font-family: \"Segoe UI\", Tahoma, Geneva, Verdana, sans-serif; line-height: 1.5;}body#bg-img{background: url(../img/background.jpeg); background-attachment: fixed; background-size: cover;}body#bg-img:after{content: \"\"; position: absolute; top: 0; right: 0; width: 100%; height: 100%; z-index: -1; background: rgba(68, 68, 68, 0.9);}.projects{grid-template-columns: repeat(4, 1fr);}.boxes{display: flex; flex-wrap: wrap; justify-content: space-evenly; align-items: center; margin-top: 1rem;}.boxes div{font-size: 2rem; border: 3px #fff solid; padding: 1.5rem 2.5rem; margin-bottom: 3rem; transition: all 0.5s ease-out;}.boxes div:hover{padding: 0.5rem 1.5rem; background: #eece1a; color: #000;}.boxes div:hover span{color: #000;}.about-info .bio-image{position: relative; bottom: 211px; right: 36px;}}@media screen and (min-width: 769px) and (max-width: 1170px){body{background: #444; color: #fff; height: 100%; margin: 0; font-family: \"Segoe UI\", Tahoma, Geneva, Verdana, sans-serif; line-height: 1.5;}body#bg-img{background: url(../img/background.jpg); background-attachment: fixed; background-size: cover;}body#bg-img:after{content: \"\"; position: absolute; top: 0; right: 0; width: 100%; height: 100%; z-index: -1; background: rgba(68, 68, 68, 0.9);}main{align-items: center; text-align: center;}main .lg-heading{line-height: 1; margin-bottom: 1rem;}main .lg-heading .sm-heading{margin: 0;}ul.menu-nav, div.menu-branding{float: none; width: 100%; min-height: 0;}ul.menu-nav.show, div.menu-branding.show{transform: translate3d(0, 0, 0);}.menu-nav{height: 75vh; transform: translate3d(-100%, 0, 0); font-size: 24px;}.menu-branding{height: 30vh; transform: translate3d(100%, 0, 0);}.menu-branding .portrait{background: url(\"../img/portrait_small.jpg\"); width: 145px; height: 145px;}.about-info{grid-template-areas: \"bioimage\" \"bio\" \"job1\" \"job2\" \"job3\"; grid-template-columns: 1fr;}.projects{grid-template-columns: repeat(2, 1fr);}.boxes{display: flex; flex-wrap: wrap; justify-content: space-evenly; align-items: center; margin-top: 1rem;}.boxes div{font-size: 2rem; border: 3px #fff solid; padding: 1.5rem 2.5rem; margin-bottom: 3rem; transition: all 0.5s ease-out;}.boxes div:hover{padding: 0.5rem 1.5rem; background: #eece1a; color: #000;}.boxes div:hover span{color: #000;}}@media screen and (min-width: 569px) and (max-width: 768px){body{background: #444; color: #fff; height: 100%; margin: 0; font-family: \"Segoe UI\", Tahoma, Geneva, Verdana, sans-serif; line-height: 1.5;}body#bg-img{background: url(../img/background.jpg); background-attachment: fixed; background-size: cover;}body#bg-img:after{content: \"\"; position: absolute; top: 0; right: 0; width: 100%; height: 100%; z-index: -1; background: rgba(68, 68, 68, 0.9);}main{align-items: center; text-align: center;}main .lg-heading{line-height: 1; margin-bottom: 1rem;}main .lg-heading .sm-heading{margin: 0;}ul.menu-nav, div.menu-branding{float: none; width: 100%; min-height: 0;}ul.menu-nav.show, div.menu-branding.show{transform: translate3d(0, 0, 0);}.menu-nav{height: 75vh; transform: translate3d(-100%, 0, 0); font-size: 24px;}.menu-branding{height: 30vh; transform: translate3d(100%, 0, 0);}.menu-branding .portrait{background: url(\"../img/portrait_small.jpg\"); width: 145px; height: 145px;}.about-info{grid-template-areas: \"bioimage\" \"bio\" \"job1\" \"job2\" \"job3\"; grid-template-columns: 1fr;}.projects{grid-template-columns: repeat(2, 1fr);}.boxes{display: flex; flex-wrap: wrap; justify-content: space-evenly; align-items: center; margin-top: 1rem;}.boxes div{font-size: 2rem; border: 3px #fff solid; padding: 1.5rem 2.5rem; margin-bottom: 3rem; transition: all 0.5s ease-out;}.boxes div:hover{padding: 0.5rem 1.5rem; background: #eece1a; color: #000;}.boxes div:hover span{color: #000;}}@media screen and (max-width: 568px){body{background: #444; color: #fff; height: 100%; margin: 0; font-family: \"Segoe UI\", Tahoma, Geneva, Verdana, sans-serif; line-height: 1.5;}body#bg-img{background: url(../img/portrait.jpg); background-repeat: no-repeat; background-attachment: fixed; background-size: cover;}body#bg-img:after{content: \"\"; position: absolute; top: 0; right: 0; width: 100%; height: 100%; z-index: -1; background: rgba(68, 68, 68, 0.9);}main{padding: 2rem;}main #home h1{margin-top: 10vh;}main .lg-heading{margin-top: 2rem; font-size: 3rem; display: block; text-align: center;}main .lg-heading .text-secondary{font-size: 3rem;}main .sm-heading{margin: 24px 0 44px 0; display: block; text-align: center; font-size: 20px;}main .icons{text-align: center;}ul.menu-nav, div.menu-branding{float: none; width: 100%; min-height: 0;}ul.menu-nav.show, div.menu-branding.show{transform: translate3d(0, 0, 0);}.menu-nav{height: 75vh; transform: translate3d(-100%, 0, 0); font-size: 24px;}.menu-branding{height: 30vh; transform: translate3d(100%, 0, 0);}.menu-branding .portrait{background: url(\"../img/portrait_small.jpg\"); width: 145px; height: 145px;}.about-info{grid-template-areas: \"bioimage\" \"bio\" \"job1\" \"job2\" \"job3\"; grid-template-columns: 1fr;}.about-info .bio-image{margin: auto; width: 70%;}.about-info .about-intro{font-size: 20px;}.projects{grid-template-columns: 1fr;}.boxes .sm1{border: #fff 3px solid; margin-bottom: 22px; text-align: center; padding: 0.5rem 1.5rem;}.boxes .sm1:hover{padding: 1.5rem 2.5rem; background: #eece1a; color: #000;}.boxes .sm1:hover span{color: #000;}.boxes .sm2{border: #fff 3px solid; margin-bottom: 22px; text-align: center; padding: 0.5rem 1.5rem;}.boxes .sm2:hover{padding: 1.5rem 2.5rem; background: #eece1a; color: #000;}.boxes .sm2:hover span{color: #000;}.boxes .sm3{border: #fff 3px solid; margin-bottom: 22px; text-align: center; padding: 0.5rem 1.5rem;}.boxes .sm3:hover{padding: 1.5rem 2.5rem; background: #eece1a; color: #000;}.boxes .sm3:hover span{color: #000;}}";

const char js[] =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/javascript\r\n"
"Connection: Close\r\n\r\n"
"const menuBtn=document.querySelector(\".menu-btn\");const menu=document.querySelector(\".menu\");const menuNav=document.querySelector(\".menu-nav\");const menuBranding=document.querySelector(\".menu-branding\");const navItems=document.querySelectorAll(\".nav-item\");let showMenu=false;menuBtn.addEventListener(\"click\", toggleMenu);function toggleMenu(){if (!showMenu){menuBtn.classList.add(\"close\"); menu.classList.add(\"show\"); menuNav.classList.add(\"show\"); menuBranding.classList.add(\"show\"); navItems.forEach(item=> item.classList.add(\"show\")); showMenu=true;}else{menuBtn.classList.remove(\"close\"); menu.classList.remove(\"show\"); menuNav.classList.remove(\"show\"); menuBranding.classList.remove(\"show\"); navItems.forEach(item=> item.classList.remove(\"show\")); showMenu=false;}}";

const char img_hdr[] =
"HTTP/1.1 200 OK\r\n"
"Content-Type: image/jpeg\r\n"
"Accept-Ranges: bytes\r\n"
"Connection: Close\r\n\r\n"
;


uint8_t img_buffer[204480] ;

int winsock_init() ;
void process_get_req(SOCKET *, char *) ;

int read_image()
{
    FILE *picture;
    int img_size ;

    picture = fopen("background.jpg", "rb");
    printf("Reading Image\r\n");

    if(picture == NULL)
    {
        printf("Error Opening Image File");
    }

    fseek(picture, 0, SEEK_END);
    img_size = ftell(picture);
    fseek(picture, 0, SEEK_SET);
    printf("Image size: %i\n",img_size);

    while(!feof(picture)) {
        fread(img_buffer, 1, 204480, picture);
    }

	return 0;
}



int main(void)
{
    char response_data[4096] , recv_buffer[1024] ;

    //Init winsock socket
    if(winsock_init() == 1)
    {   return 1 ; }

    // create socket
    SOCKET server_skt, client_skt ;

    struct sockaddr_in server_addr ;
    server_skt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) ;
    server_addr.sin_family = AF_INET ;
    server_addr.sin_port = htons(SERVER_PORT) ;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR) ;

    //Bind a socket
    if (bind(server_skt,(struct sockaddr *)&server_addr,sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Bind failed\n\r");
        printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(server_skt);
        WSACleanup();
        return 1;
    }
    printf("Http Server started at %s on port %d\r\n",SERVER_ADDR,SERVER_PORT);
    listen(server_skt,5) ;      // listen for connections, at max 5 simultaineous connections

    while(1)
    {
        memset(recv_buffer,0x00,sizeof(recv_buffer));
        client_skt = accept(server_skt,NULL,NULL) ;     //blocking call
        if(client_skt != INVALID_SOCKET)
        {
            recv(client_skt,recv_buffer,1024,0) ;
            if(strncmp(recv_buffer,"GET",3) == 0)
            {
                // process get request
                process_get_req(&client_skt,recv_buffer) ;

            }
            if(strncmp(recv_buffer,"POST",4) == 0)
            {
                // process post request

            }
        }
        closesocket(client_skt);
    }
    return 0 ;
}


void process_get_req(SOCKET *client_skt, char *buffer)
{
    printf("GET Request recieved: %s\r\n", buffer) ;
    if((strncmp(buffer, "GET / ", 6) == 0) || (strncmp(buffer, "GET /index.html", 15) == 0))
    {
        send(*client_skt,(char *)intro,strlen(intro),IPPROTO_IP)  ;
    }
    else if( strncmp(buffer, "GET /css/main.css", 17) == 0)
    {
        send(*client_skt,(char *)stylesheet,strlen(stylesheet),IPPROTO_IP) ;
    }
    else if( strncmp(buffer, "GET /js/main.js", 15) == 0)
    {
        send(*client_skt,(char *)js,strlen(js),IPPROTO_IP) ;
    }
    else if( strncmp(buffer, "GET /img/background.jpeg", 24) == 0)
    {
        read_image() ;
        send(*client_skt,(char *)img_hdr,strlen(img_hdr),IPPROTO_IP) ;
        send(*client_skt,(char *)img_buffer,204479,IPPROTO_IP)  ;
    }

}

void process_post_req(char *buffer)
{

}


int winsock_init()
{
    WSADATA wsa;
    printf("\nInitialising Winsock...\n\r");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError()) ;
		return 1 ;
	}
	printf("Winsock Initialised.\r\n") ;

}
