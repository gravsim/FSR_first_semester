const int fig_num = 1;

vec3[9] vertices = vec3[](
    vec3(0.3, 0.2, 2.),
    vec3(0.7, 0.3, 2.),
    vec3(0.6, 0.8, 2.),
    vec3(0.1, 0.6, 4.),
    
    vec3(0.8, 0.5, 3.),
    vec3(0.7, 0.1, 4.),

    vec3(0.5, 0.3, 3.),
    vec3(0.4, 0.8, 1.),
    vec3(0.2, 0.9, 4.)
);

vec3[9] fig_vertices = vec3[](
    vertices[0],
    vec3(0.7, 0.3, 2.),
    vec3(0.6, 0.8, 2.),
    vec3(0.1, 0.6, 4.),
    
    vec3(0.8, 0.5, 3.),
    vec3(0.7, 0.1, 4.),

    vec3(0.5, 0.3, 3.),
    vec3(0.4, 0.8, 1.),
    vec3(0.2, 0.9, 4.)
);
int[fig_num+1] csr_indices = int[](0, 4);
vec3[6] colors = vec3[](
    vec3(0., 0., 1.),
    vec3(0., 1., 0.),
    vec3(1., 0., 0.),
    vec3(0., 1., 1.),
    vec3(1., 1., 0.),
    vec3(1., 0., 1.)
);


void rotate_y(out vec3 vector, in vec3 center) {
    float t = iTime;
    vector = mat3(cos(t), 0, sin(t), 0, 1, 0, -sin(t), 0, cos(t)) * (vector - center) + center;
}


void rotate(in int i) {
    int j;
    int start = csr_indices[i];
    int end = csr_indices[i+1];
    for (j = start; j < end; j++) {
        rotate_y(fig_vertices[j], fig_vertices[0]);
    }
}

float cross2(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}


bool intersect_fig(in vec2 uv, in int i) {
    int j;
    int start = csr_indices[i];
    int end = csr_indices[i+1];
    vec3 edge = fig_vertices[start] - fig_vertices[end-1];
    float first_sign = sign(cross2(edge.xy, uv - fig_vertices[start].xy));
    int next;
    for (j = start; j < end; j++) {
        if (j + 1 < end) {
            next = j+1;
        } else {
            next = start;
        }
        edge = fig_vertices[next] - fig_vertices[j];
        if (sign(cross2(edge.xy, uv - fig_vertices[j].xy)) != first_sign) {
            return false;
        }
    }
    return true;
    
}


float get_z_fig(in vec2 uv, in int i, in vec3 dot1, in vec3 dot2, in vec3 dot3) {
    vec3 dif1 = dot2 - dot1;
    vec3 dif2 = dot3 - dot2;
    vec3 norm = cross(dif2, dif1);
    float D = -dot(norm, dot1);
    float z = -(norm.x * uv.x + norm.y * uv.y + D) / norm.z;
    return z;
}


void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    rotate(0);
    vec2 uv = fragCoord/iResolution.xy;
    float z;
    vec3 background = vec3(0., 0., 0.);
    vec3 fig_color = vec3(1., 0., 0.);
    int i;
    int index;
    vec3 col = background;
    float z_max = -5.;
    float z_tmp;
    for (i = 0; i < fig_num; i++) {
        if(intersect_fig(uv, i)) {
            z_tmp = get_z_fig(uv, i, fig_vertices[csr_indices[i]], fig_vertices[csr_indices[i]+1], fig_vertices[csr_indices[i]+2]);
            if (z_tmp > z_max) {
                z_max = z_tmp;
                col = colors[i];
            }
        }
    }
    fragColor = vec4(col, 1.0);
}