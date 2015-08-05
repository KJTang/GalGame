#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
varying vec4 v_fragmentColor;

void main()
{
    gl_FragColor = texture2D(CC_Texture0, v_texCoord);
    if (gl_FragColor.a > 0.0) {
        gl_FragColor.rgb = v_fragmentColor.rgb;
    }
}