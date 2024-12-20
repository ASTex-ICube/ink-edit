#version 330 core

uniform vec2 uRes;
uniform float uFprinc;
uniform float uFspread;
uniform float uOprinc;
uniform float uOspread;
uniform float uSeed;

out float FragColor;

// CONSTANTE -----------------------------
const float PI = acos(-1.0);
const float TWICE_PI = 2.0*PI;

// ---- tools -------------------------------------
float rndi(int i, int j, float seed)
{
    return fract(1e5*sin(float(i)+3.*float(j)+seed)); // 0.567
}

float gaussian(float x, float size){
    return exp(-(x*x)/(2.*size*size));
}

// ---- gabor noise -------------------------------------
float gabor(vec2 position, vec2 offset, vec2 direction, float freq, float kernel_size)
{
    // cloche gaussienne
    float gauss = gaussian((position-offset).x, kernel_size)*gaussian((position-offset).y, kernel_size);

    // sinusoides complexe
    vec2 OP = position-offset;
    float op_d = dot(OP, direction);
    float cosinus = cos(TWICE_PI*freq*op_d); // partie réel
    float sinus = sin(TWICE_PI*freq*op_d); // partie imaginaire


    // dérivation complexe
    vec2 d_cos = -OP/(kernel_size*kernel_size) * cosinus - TWICE_PI*freq*direction * sinus; // partie réel
    vec2 d_sin = -OP/(kernel_size*kernel_size) * sinus + TWICE_PI*freq*direction * cosinus; // partie imaginaire

    return gauss*cosinus;// vec3(sinus, d_sin);
}


float Gabor_noise(vec2 uv, int nb_kernel, float freq_princ, float freq_spread, float omega_princ, float omega_spread, float seed, float kernel_size)
{
    float noises= 0.;
    float var = 0.;

    for (int i=0; i<nb_kernel; i++) {

        float Omega = omega_princ + omega_spread*(2.*rndi(i, 2, seed) -1.) + 0.5*rndi(i, 5, seed);
        float Freq = freq_princ + freq_spread*(2.*rndi(i, 4, seed) -1.) + rndi(i, 6, seed);

        vec2 pos = 1.2*vec2(rndi(i,0, seed),rndi(i,1, seed))-vec2(0.1);
        vec2 dir = vec2(cos(Omega), sin(Omega));

        float wi = 2.*rndi(i, 3, seed) -1.;

        float gabor_noise = wi*gabor(uv, pos, dir, Freq, kernel_size);

        var += wi*wi* 0.5*(PI*kernel_size*kernel_size)*(1 + exp(-Freq*Freq * kernel_size*kernel_size));
        noises += gabor_noise;
    }

    return noises/sqrt(var-0.5*0.5); // division par racine de var pour avoir une variance de 1
}

void main() {
    float res = max(uRes.x, uRes.y);
    vec2 uv = (gl_FragCoord.xy/res);

    int nb_kernel = 10*int(uFprinc);// 100;
    float size_kernel = max(2.4/uFprinc, 0.05);// 0.0566;// 0.08;


    float noise = Gabor_noise(uv, nb_kernel, uFprinc, uFspread, uOprinc, uOspread, uSeed*0.624, size_kernel);
    //noise = 0.5 + 0.155*noise; // *0.155 -> variance de 0.155*0.155 = 0,024025; +0.5 -> moyenne de 0.5

    FragColor = 0.5 + 0.155*noise;
}
