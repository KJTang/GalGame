#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform int u_blur;

void main(void)
{
    if (u_blur == 0) {
        gl_FragColor = texture2D(CC_Texture0, v_texCoord);
    } else {
        vec2 p_offset[5];
        p_offset[0] = vec2(0.0, 0.0);
        p_offset[1] = vec2(-1.0, 0.0);
        p_offset[2] = vec2(1.0, 0.0);
        p_offset[3] = vec2(0.0, -1.0);
        p_offset[4] = vec2(0.0, 1.0);
        float p_weight[5];
        p_weight[0] = 0.40;
        p_weight[1] = 0.15;
        p_weight[2] = 0.15;
        p_weight[3] = 0.15;
        p_weight[4] = 0.15;
        
        vec2 pix_size = 1.0/vec2(u_blur, u_blur);
        
        vec4 sample = vec4(0, 0, 0, 0);
        for (int i = 0; i < 5; i += 1) {
            sample += texture2D(CC_Texture0, v_texCoord + p_offset[i] * pix_size) * p_weight[i];
        }
        gl_FragColor = sample;
    }
}