#include<stdio.h>
#include<math.h>

#define len 256
#define log2N 8


#define Pi 3.1415

#define Wn Wn_256
#define WnLen 256


typedef struct{
    double real;
    double img;
}C;



unsigned int pLen=WnLen*2/len;

const C Wn_16[16]={
    { 1.0 , -0.0 } ,
{ 0.9807852804032304 , -0.19509032201612825 } ,
{ 0.9238795325112867 , -0.3826834323650898 } ,
{ 0.8314696123025452 , -0.5555702330196022 } ,
{ 0.7071067811865476 , -0.7071067811865476 } ,
{ 0.5555702330196023 , -0.8314696123025452 } ,
{ 0.38268343236508984 , -0.9238795325112867 } ,
{ 0.19509032201612833 , -0.9807852804032304 } ,
{ 6.123233995736766e-17 , -1.0 } ,
{ -0.1950903220161282 , -0.9807852804032304 } ,
{ -0.3826834323650897 , -0.9238795325112867 } ,
{ -0.555570233019602 , -0.8314696123025453 } ,
{ -0.7071067811865475 , -0.7071067811865476 } ,
{ -0.8314696123025453 , -0.5555702330196022 } ,
{ -0.9238795325112867 , -0.3826834323650899 } ,
{ -0.9807852804032304 , -0.1950903220161286 } ,
};

const C Wn_64[64]={
    { 1.0 , -0.0 } ,
{ 0.9987954562051724 , -0.049067674327418015 } ,
{ 0.9951847266721969 , -0.0980171403295606 } ,
{ 0.989176509964781 , -0.14673047445536175 } ,
{ 0.9807852804032304 , -0.19509032201612825 } ,
{ 0.970031253194544 , -0.24298017990326387 } ,
{ 0.9569403357322088 , -0.29028467725446233 } ,
{ 0.9415440651830208 , -0.33688985339222005 } ,
{ 0.9238795325112867 , -0.3826834323650898 } ,
{ 0.9039892931234433 , -0.4275550934302821 } ,
{ 0.881921264348355 , -0.47139673682599764 } ,
{ 0.8577286100002721 , -0.5141027441932217 } ,
{ 0.8314696123025452 , -0.5555702330196022 } ,
{ 0.8032075314806449 , -0.5956993044924334 } ,
{ 0.773010453362737 , -0.6343932841636455 } ,
{ 0.7409511253549592 , -0.6715589548470183 } ,
{ 0.7071067811865476 , -0.7071067811865476 } ,
{ 0.6715589548470183 , -0.7409511253549591 } ,
{ 0.6343932841636455 , -0.7730104533627369 } ,
{ 0.5956993044924335 , -0.8032075314806448 } ,
{ 0.5555702330196023 , -0.8314696123025452 } ,
{ 0.5141027441932217 , -0.8577286100002721 } ,
{ 0.4713967368259978 , -0.8819212643483549 } ,
{ 0.4275550934302822 , -0.9039892931234433 } ,
{ 0.38268343236508984 , -0.9238795325112867 } ,
{ 0.33688985339222005 , -0.9415440651830208 } ,
{ 0.29028467725446233 , -0.9569403357322089 } ,
{ 0.24298017990326398 , -0.970031253194544 } ,
{ 0.19509032201612833 , -0.9807852804032304 } ,
{ 0.14673047445536175 , -0.989176509964781 } ,
{ 0.09801714032956077 , -0.9951847266721968 } ,
{ 0.049067674327418126 , -0.9987954562051724 } ,
{ 6.123233995736766e-17 , -1.0 } ,
{ -0.04906767432741801 , -0.9987954562051724 } ,
{ -0.09801714032956065 , -0.9951847266721969 } ,
{ -0.14673047445536164 , -0.989176509964781 } ,
{ -0.1950903220161282 , -0.9807852804032304 } ,
{ -0.24298017990326387 , -0.970031253194544 } ,
{ -0.29028467725446216 , -0.9569403357322089 } ,
{ -0.33688985339221994 , -0.9415440651830208 } ,
{ -0.3826834323650897 , -0.9238795325112867 } ,
{ -0.42755509343028186 , -0.9039892931234434 } ,
{ -0.4713967368259977 , -0.881921264348355 } ,
{ -0.5141027441932216 , -0.8577286100002721 } ,
{ -0.555570233019602 , -0.8314696123025453 } ,
{ -0.5956993044924334 , -0.8032075314806449 } ,
{ -0.6343932841636454 , -0.7730104533627371 } ,
{ -0.6715589548470184 , -0.740951125354959 } ,
{ -0.7071067811865475 , -0.7071067811865476 } ,
{ -0.7409511253549589 , -0.6715589548470186 } ,
{ -0.773010453362737 , -0.6343932841636455 } ,
{ -0.8032075314806448 , -0.5956993044924335 } ,
{ -0.8314696123025453 , -0.5555702330196022 } ,
{ -0.857728610000272 , -0.5141027441932218 } ,
{ -0.8819212643483549 , -0.4713967368259978 } ,
{ -0.9039892931234433 , -0.42755509343028203 } ,
{ -0.9238795325112867 , -0.3826834323650899 } ,
{ -0.9415440651830207 , -0.33688985339222033 } ,
{ -0.9569403357322088 , -0.2902846772544624 } ,
{ -0.970031253194544 , -0.24298017990326407 } ,
{ -0.9807852804032304 , -0.1950903220161286 } ,
{ -0.989176509964781 , -0.1467304744553618 } ,
{ -0.9951847266721968 , -0.09801714032956083 } ,
{ -0.9987954562051724 , -0.049067674327417966 } ,
};


const C Wn_256[256] ={
    { 1.0 , -0.0 } ,
{ 0.9999247018391445 , -0.012271538285719925 } ,
{ 0.9996988186962042 , -0.024541228522912288 } ,
{ 0.9993223845883495 , -0.03680722294135883 } ,
{ 0.9987954562051724 , -0.049067674327418015 } ,
{ 0.9981181129001492 , -0.06132073630220858 } ,
{ 0.9972904566786902 , -0.07356456359966743 } ,
{ 0.996312612182778 , -0.0857973123444399 } ,
{ 0.9951847266721969 , -0.0980171403295606 } ,
{ 0.9939069700023561 , -0.11022220729388306 } ,
{ 0.99247953459871 , -0.1224106751992162 } ,
{ 0.99090263542778 , -0.13458070850712617 } ,
{ 0.989176509964781 , -0.14673047445536175 } ,
{ 0.9873014181578584 , -0.15885814333386145 } ,
{ 0.9852776423889412 , -0.17096188876030122 } ,
{ 0.9831054874312163 , -0.18303988795514095 } ,
{ 0.9807852804032304 , -0.19509032201612825 } ,
{ 0.9783173707196277 , -0.20711137619221856 } ,
{ 0.9757021300385286 , -0.2191012401568698 } ,
{ 0.9729399522055602 , -0.2310581082806711 } ,
{ 0.970031253194544 , -0.24298017990326387 } ,
{ 0.9669764710448521 , -0.25486565960451457 } ,
{ 0.9637760657954398 , -0.26671275747489837 } ,
{ 0.9604305194155658 , -0.27851968938505306 } ,
{ 0.9569403357322088 , -0.29028467725446233 } ,
{ 0.9533060403541939 , -0.3020059493192281 } ,
{ 0.9495281805930367 , -0.3136817403988915 } ,
{ 0.9456073253805213 , -0.3253102921622629 } ,
{ 0.9415440651830208 , -0.33688985339222005 } ,
{ 0.937339011912575 , -0.34841868024943456 } ,
{ 0.932992798834739 , -0.3598950365349881 } ,
{ 0.9285060804732156 , -0.37131719395183754 } ,
{ 0.9238795325112867 , -0.3826834323650898 } ,
{ 0.9191138516900578 , -0.3939920400610481 } ,
{ 0.9142097557035307 , -0.40524131400498986 } ,
{ 0.9091679830905224 , -0.41642956009763715 } ,
{ 0.9039892931234433 , -0.4275550934302821 } ,
{ 0.8986744656939538 , -0.43861623853852766 } ,
{ 0.8932243011955153 , -0.44961132965460654 } ,
{ 0.8876396204028539 , -0.46053871095824 } ,
{ 0.881921264348355 , -0.47139673682599764 } ,
{ 0.8760700941954066 , -0.4821837720791227 } ,
{ 0.8700869911087115 , -0.49289819222978404 } ,
{ 0.8639728561215867 , -0.5035383837257176 } ,
{ 0.8577286100002721 , -0.5141027441932217 } ,
{ 0.8513551931052652 , -0.524589682678469 } ,
{ 0.8448535652497071 , -0.5349976198870972 } ,
{ 0.8382247055548381 , -0.5453249884220465 } ,
{ 0.8314696123025452 , -0.5555702330196022 } ,
{ 0.8245893027850253 , -0.5657318107836131 } ,
{ 0.8175848131515837 , -0.5758081914178453 } ,
{ 0.8104571982525948 , -0.5857978574564389 } ,
{ 0.8032075314806449 , -0.5956993044924334 } ,
{ 0.7958369046088836 , -0.6055110414043255 } ,
{ 0.7883464276266062 , -0.6152315905806268 } ,
{ 0.7807372285720945 , -0.6248594881423863 } ,
{ 0.773010453362737 , -0.6343932841636455 } ,
{ 0.765167265622459 , -0.6438315428897914 } ,
{ 0.7572088465064846 , -0.6531728429537768 } ,
{ 0.7491363945234594 , -0.6624157775901718 } ,
{ 0.7409511253549592 , -0.6715589548470183 } ,
{ 0.7326542716724128 , -0.680600997795453 } ,
{ 0.724247082951467 , -0.6895405447370668 } ,
{ 0.7157308252838187 , -0.6983762494089728 } ,
{ 0.7071067811865476 , -0.7071067811865476 } ,
{ 0.6983762494089729 , -0.7157308252838186 } ,
{ 0.6895405447370669 , -0.7242470829514669 } ,
{ 0.680600997795453 , -0.7326542716724128 } ,
{ 0.6715589548470183 , -0.7409511253549591 } ,
{ 0.6624157775901718 , -0.7491363945234593 } ,
{ 0.6531728429537769 , -0.7572088465064846 } ,
{ 0.6438315428897915 , -0.765167265622459 } ,
{ 0.6343932841636455 , -0.7730104533627369 } ,
{ 0.6248594881423865 , -0.7807372285720945 } ,
{ 0.6152315905806268 , -0.7883464276266062 } ,
{ 0.6055110414043255 , -0.7958369046088835 } ,
{ 0.5956993044924335 , -0.8032075314806448 } ,
{ 0.5857978574564389 , -0.8104571982525948 } ,
{ 0.5758081914178453 , -0.8175848131515837 } ,
{ 0.5657318107836132 , -0.8245893027850253 } ,
{ 0.5555702330196023 , -0.8314696123025452 } ,
{ 0.5453249884220465 , -0.838224705554838 } ,
{ 0.5349976198870973 , -0.844853565249707 } ,
{ 0.5245896826784688 , -0.8513551931052652 } ,
{ 0.5141027441932217 , -0.8577286100002721 } ,
{ 0.5035383837257176 , -0.8639728561215867 } ,
{ 0.4928981922297841 , -0.8700869911087113 } ,
{ 0.48218377207912283 , -0.8760700941954066 } ,
{ 0.4713967368259978 , -0.8819212643483549 } ,
{ 0.46053871095824 , -0.8876396204028539 } ,
{ 0.4496113296546066 , -0.8932243011955153 } ,
{ 0.4386162385385277 , -0.8986744656939538 } ,
{ 0.4275550934302822 , -0.9039892931234433 } ,
{ 0.4164295600976373 , -0.9091679830905223 } ,
{ 0.40524131400498986 , -0.9142097557035307 } ,
{ 0.3939920400610481 , -0.9191138516900578 } ,
{ 0.38268343236508984 , -0.9238795325112867 } ,
{ 0.3713171939518376 , -0.9285060804732156 } ,
{ 0.3598950365349883 , -0.9329927988347388 } ,
{ 0.3484186802494345 , -0.937339011912575 } ,
{ 0.33688985339222005 , -0.9415440651830208 } ,
{ 0.325310292162263 , -0.9456073253805213 } ,
{ 0.3136817403988916 , -0.9495281805930367 } ,
{ 0.3020059493192282 , -0.9533060403541938 } ,
{ 0.29028467725446233 , -0.9569403357322089 } ,
{ 0.27851968938505306 , -0.9604305194155658 } ,
{ 0.2667127574748984 , -0.9637760657954398 } ,
{ 0.2548656596045146 , -0.9669764710448521 } ,
{ 0.24298017990326398 , -0.970031253194544 } ,
{ 0.23105810828067128 , -0.9729399522055601 } ,
{ 0.21910124015686977 , -0.9757021300385286 } ,
{ 0.20711137619221856 , -0.9783173707196277 } ,
{ 0.19509032201612833 , -0.9807852804032304 } ,
{ 0.18303988795514106 , -0.9831054874312163 } ,
{ 0.17096188876030136 , -0.9852776423889412 } ,
{ 0.1588581433338614 , -0.9873014181578584 } ,
{ 0.14673047445536175 , -0.989176509964781 } ,
{ 0.13458070850712622 , -0.99090263542778 } ,
{ 0.12241067519921628 , -0.99247953459871 } ,
{ 0.11022220729388318 , -0.9939069700023561 } ,
{ 0.09801714032956077 , -0.9951847266721968 } ,
{ 0.08579731234443988 , -0.996312612182778 } ,
{ 0.07356456359966745 , -0.9972904566786902 } ,
{ 0.06132073630220865 , -0.9981181129001492 } ,
{ 0.049067674327418126 , -0.9987954562051724 } ,
{ 0.03680722294135899 , -0.9993223845883495 } ,
{ 0.024541228522912264 , -0.9996988186962042 } ,
{ 0.012271538285719944 , -0.9999247018391445 } ,
{ 6.123233995736766e-17 , -1.0 } ,
{ -0.012271538285719823 , -0.9999247018391445 } ,
{ -0.024541228522912142 , -0.9996988186962042 } ,
{ -0.036807222941358866 , -0.9993223845883495 } ,
{ -0.04906767432741801 , -0.9987954562051724 } ,
{ -0.06132073630220853 , -0.9981181129001492 } ,
{ -0.07356456359966733 , -0.9972904566786902 } ,
{ -0.08579731234443976 , -0.996312612182778 } ,
{ -0.09801714032956065 , -0.9951847266721969 } ,
{ -0.11022220729388306 , -0.9939069700023561 } ,
{ -0.12241067519921615 , -0.99247953459871 } ,
{ -0.1345807085071261 , -0.99090263542778 } ,
{ -0.14673047445536164 , -0.989176509964781 } ,
{ -0.15885814333386128 , -0.9873014181578584 } ,
{ -0.17096188876030124 , -0.9852776423889412 } ,
{ -0.18303988795514092 , -0.9831054874312163 } ,
{ -0.1950903220161282 , -0.9807852804032304 } ,
{ -0.20711137619221845 , -0.9783173707196277 } ,
{ -0.21910124015686966 , -0.9757021300385286 } ,
{ -0.23105810828067114 , -0.9729399522055602 } ,
{ -0.24298017990326387 , -0.970031253194544 } ,
{ -0.2548656596045145 , -0.9669764710448521 } ,
{ -0.2667127574748983 , -0.9637760657954398 } ,
{ -0.27851968938505295 , -0.9604305194155659 } ,
{ -0.29028467725446216 , -0.9569403357322089 } ,
{ -0.3020059493192281 , -0.9533060403541939 } ,
{ -0.3136817403988914 , -0.9495281805930367 } ,
{ -0.32531029216226287 , -0.9456073253805214 } ,
{ -0.33688985339221994 , -0.9415440651830208 } ,
{ -0.3484186802494344 , -0.937339011912575 } ,
{ -0.35989503653498817 , -0.9329927988347388 } ,
{ -0.3713171939518375 , -0.9285060804732156 } ,
{ -0.3826834323650897 , -0.9238795325112867 } ,
{ -0.393992040061048 , -0.9191138516900578 } ,
{ -0.40524131400498975 , -0.9142097557035307 } ,
{ -0.416429560097637 , -0.9091679830905225 } ,
{ -0.42755509343028186 , -0.9039892931234434 } ,
{ -0.4386162385385274 , -0.8986744656939539 } ,
{ -0.4496113296546067 , -0.8932243011955152 } ,
{ -0.46053871095824006 , -0.8876396204028539 } ,
{ -0.4713967368259977 , -0.881921264348355 } ,
{ -0.4821837720791227 , -0.8760700941954066 } ,
{ -0.492898192229784 , -0.8700869911087115 } ,
{ -0.5035383837257175 , -0.8639728561215868 } ,
{ -0.5141027441932216 , -0.8577286100002721 } ,
{ -0.5245896826784687 , -0.8513551931052652 } ,
{ -0.534997619887097 , -0.8448535652497072 } ,
{ -0.5453249884220462 , -0.8382247055548382 } ,
{ -0.555570233019602 , -0.8314696123025453 } ,
{ -0.5657318107836132 , -0.8245893027850252 } ,
{ -0.5758081914178453 , -0.8175848131515837 } ,
{ -0.5857978574564389 , -0.8104571982525948 } ,
{ -0.5956993044924334 , -0.8032075314806449 } ,
{ -0.6055110414043254 , -0.7958369046088836 } ,
{ -0.6152315905806267 , -0.7883464276266063 } ,
{ -0.6248594881423862 , -0.7807372285720946 } ,
{ -0.6343932841636454 , -0.7730104533627371 } ,
{ -0.6438315428897913 , -0.7651672656224591 } ,
{ -0.6531728429537765 , -0.7572088465064847 } ,
{ -0.6624157775901719 , -0.7491363945234593 } ,
{ -0.6715589548470184 , -0.740951125354959 } ,
{ -0.680600997795453 , -0.7326542716724128 } ,
{ -0.6895405447370669 , -0.7242470829514669 } ,
{ -0.6983762494089728 , -0.7157308252838187 } ,
{ -0.7071067811865475 , -0.7071067811865476 } ,
{ -0.7157308252838186 , -0.6983762494089729 } ,
{ -0.7242470829514668 , -0.689540544737067 } ,
{ -0.7326542716724127 , -0.6806009977954532 } ,
{ -0.7409511253549589 , -0.6715589548470186 } ,
{ -0.7491363945234591 , -0.662415777590172 } ,
{ -0.7572088465064847 , -0.6531728429537766 } ,
{ -0.765167265622459 , -0.6438315428897914 } ,
{ -0.773010453362737 , -0.6343932841636455 } ,
{ -0.7807372285720945 , -0.6248594881423863 } ,
{ -0.7883464276266062 , -0.6152315905806269 } ,
{ -0.7958369046088835 , -0.6055110414043257 } ,
{ -0.8032075314806448 , -0.5956993044924335 } ,
{ -0.8104571982525947 , -0.585797857456439 } ,
{ -0.8175848131515836 , -0.5758081914178454 } ,
{ -0.8245893027850251 , -0.5657318107836135 } ,
{ -0.8314696123025453 , -0.5555702330196022 } ,
{ -0.8382247055548381 , -0.5453249884220464 } ,
{ -0.8448535652497071 , -0.5349976198870972 } ,
{ -0.8513551931052652 , -0.524589682678469 } ,
{ -0.857728610000272 , -0.5141027441932218 } ,
{ -0.8639728561215867 , -0.5035383837257176 } ,
{ -0.8700869911087113 , -0.49289819222978415 } ,
{ -0.8760700941954065 , -0.4821837720791229 } ,
{ -0.8819212643483549 , -0.4713967368259978 } ,
{ -0.8876396204028538 , -0.4605387109582402 } ,
{ -0.8932243011955152 , -0.4496113296546069 } ,
{ -0.8986744656939539 , -0.43861623853852755 } ,
{ -0.9039892931234433 , -0.42755509343028203 } ,
{ -0.9091679830905224 , -0.41642956009763715 } ,
{ -0.9142097557035307 , -0.4052413140049899 } ,
{ -0.9191138516900578 , -0.39399204006104815 } ,
{ -0.9238795325112867 , -0.3826834323650899 } ,
{ -0.9285060804732155 , -0.3713171939518377 } ,
{ -0.9329927988347388 , -0.35989503653498833 } ,
{ -0.9373390119125748 , -0.3484186802494348 } ,
{ -0.9415440651830207 , -0.33688985339222033 } ,
{ -0.9456073253805212 , -0.32531029216226326 } ,
{ -0.9495281805930367 , -0.3136817403988914 } ,
{ -0.9533060403541939 , -0.30200594931922803 } ,
{ -0.9569403357322088 , -0.2902846772544624 } ,
{ -0.9604305194155658 , -0.27851968938505317 } ,
{ -0.9637760657954398 , -0.2667127574748985 } ,
{ -0.9669764710448521 , -0.2548656596045147 } ,
{ -0.970031253194544 , -0.24298017990326407 } ,
{ -0.9729399522055601 , -0.23105810828067133 } ,
{ -0.9757021300385285 , -0.21910124015687005 } ,
{ -0.9783173707196275 , -0.20711137619221884 } ,
{ -0.9807852804032304 , -0.1950903220161286 } ,
{ -0.9831054874312163 , -0.1830398879551409 } ,
{ -0.9852776423889412 , -0.17096188876030122 } ,
{ -0.9873014181578584 , -0.15885814333386147 } ,
{ -0.989176509964781 , -0.1467304744553618 } ,
{ -0.99090263542778 , -0.13458070850712628 } ,
{ -0.99247953459871 , -0.12241067519921635 } ,
{ -0.9939069700023561 , -0.11022220729388324 } ,
{ -0.9951847266721968 , -0.09801714032956083 } ,
{ -0.996312612182778 , -0.08579731234444016 } ,
{ -0.9972904566786902 , -0.07356456359966773 } ,
{ -0.9981181129001492 , -0.06132073630220849 } ,
{ -0.9987954562051724 , -0.049067674327417966 } ,
{ -0.9993223845883495 , -0.03680722294135883 } ,
{ -0.9996988186962042 , -0.024541228522912326 } ,
{ -0.9999247018391445 , -0.012271538285720007 } ,
};

C input[len];

C output[len];


C add(C a, C b){
    C c;
    c.real=a.real+b.real;
    c.img=a.img+b.img;
    return c;
}

C sub(C a,C b){
    C c;
    c.real=a.real-b.real;
    c.img=a.img-b.img;
    return c;
}

C mul(C a,C b){
    C c;
    c.real=a.real*b.real-a.img*b.img;
    c.img=a.real*b.img+a.img*b.real;
    return c;
}

void Reverse(){                                                                                       //翻转运算
    for(unsigned int i=0;i<len;i++){
        unsigned int I=i;
        unsigned int R=0;
        for(unsigned char bit=0;bit<log2N;bit++){
            R<<=1;
            R|=(I&1);
            I>>=1;
        }
        if(R>i){
            C tmp=input[R];
            input[R]=input[i];
            input[i]=tmp;
        }
    }
}

void ButterflyAlgorithm(){
    for(unsigned int i=1;i<=len;i<<=1){
        for(unsigned int j=0;j<(len/(2*i));j++){
            for(unsigned int k=0;k<i;k++){
                C tmpXw=mul(input[j*2*i+k+i],Wn[WnLen*k/i]);
                C tmpTop=add(input[j*2*i+k],tmpXw);
                C tmpBottom=sub(input[j*2*i+k],tmpXw);
                input[j*2*i+k]=tmpTop;
                input[j*2*i+k+i]=tmpBottom;
            }
        }
    }
}



void fft(){                                                                                            //快速傅里叶变换
    Reverse();
    ButterflyAlgorithm();
    for(unsigned int i=0;i<len;i++){
        output[i].real=sqrt(input[i].real*input[i].real+input[i].img*input[i].img);
    }
}

// 在len个点中，如果包含x个正弦周期，就是output[x]为峰值。
int main(){
    double period=122;

    double freq=period *2*Pi/len;

    for(int i=0;i<len;i++){
        input[i].real=cos(i*freq);
    }

    fft();


    //横着显示频谱
    double tmpMax=0;
    printf("\n\n");
    for(int i=0;i<len/2;i++){
        if(tmpMax<output[i].real){
            tmpMax=output[i].real;
        }
    }
    for(int i=tmpMax;i>0;i--){
        for(int j=0;j<len/2;j++){
            if(output[j].real>i){
                printf("H");
            }else{
                printf(" ");
            }
            if(j==(len/2-1)){
                printf("| ");
            }
        }
        printf("\n");
    }
    for(int i=0;i<len/2;i++){
        printf("%d",i%10);
        if(i==(len/2-1)){
            printf("| ");
        }
    }




    //竖着显示频谱
    /*
    for(int i=0;i<len;i++){
        
        for(int lo=0;lo<output[i].real;lo++){
            printf("-");
        }
        if(i==(len/2-1)){
            printf("\n\n----------------------------------------------------------------------\n");
        }
        printf("\n");
    }
    */


    return 0;
}