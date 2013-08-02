varying vec4 vColor;

void main() {
    vec3 nais = vColor.rgb/max(max(vColor.r,vColor.g),vColor.b);
    nais = abs((nais*2.0)-1.0);
    nais = floor(nais*5.0001)/5;
    gl_FragColor = vec4(nais,1.0);
}
