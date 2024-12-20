//
// Created by grenier on 28/05/24.
//

#ifndef ASTEX_CCVT_APPLICATION_H
#define ASTEX_CCVT_APPLICATION_H

#include "ccvt.h"

// Forward declare
struct GLFWwindow;

struct point_info{
    float _x;
    float _y;
    float _w;
    float _sel;

    point_info(float x, float y, float w):_x(x), _y(y), _w(w), _sel(0.){};
};

struct cell_info{
    float _cap;
    float _r = 0.;
    float _g = 0.;
    float _b = 0.;

    cell_info(float cap, float r, float g, float b):_cap(cap), _r(r), _g(g), _b(b){};
};

struct histo_info{
    int _count;
    float _obj;
    float _r;
    float _g;
    float _b;

    histo_info(float r, float g, float b): _count(0), _obj(0.), _r(r), _g(g), _b(b){};
    void incr(){_count++;}
};

struct selection{
    bool active = false;
    bool toogle = false;
    int id = -1;
};

class ccvt_application {
public:
    // A function called only once at the beginning. Returns false is init failed.
    bool onInit();

    // A function called only once at the very end.
    void onFinish();

    // A function that tells if the application is still running.
    bool isRunning();

    // A function called at each frame, guaranteed never to be called before `onInit`.
    void onFrame();

    void attacheCCVT(CCVT &ccvt){
        m_ccvt = ccvt;
        m_size_density = m_ccvt.get_domain_size_x();
        m_size_density = m_ccvt.get_domain_size_y();
        m_max_val = m_ccvt.get_domain_max_val();
    }

private:
    bool init_noise();

    void drawNoise(unsigned int &fbo, float width, float height, float freq_princ, float freq_spread, float omega_princ, float omega_spread, float seed);
    void drawCM();
    void drawComposition();

    bool initGui(GLFWwindow* &window);
    void terminateGui();
    void updateGui();
    void cellPopup(int id);

    void addPoint(float xPos, float yPos, float r, float g, float b);
    void insertPoint(int vecPos, float xPos, float yPos, float r, float g, float b);
    void deletePoint(int id);
    void normilizeCap();
    void equalizeCap();

    void getCCVTcells();
    void getCCVTadjGraph();
    void optimizeCCVT();
    void updateCCVT();

    static void saveTexture(unsigned  int fbo_id, int width, int height, const std::string &filename);
    void saveData(const std::string &filename);

    static void computeStatistiques(unsigned int fbo_id, int width, int height, float &mean, float &var);
    static float computeMean(const std::vector<float>& data);
    static float computeSquareMean(const std::vector<float>& data);
    void computeProportions();
    void drawConvertNoise1ToRGB();
    void drawConvertNoise2ToRGB();
    void reduceNoiseView();
    void increaseNoiseView();
    void changeNoiseView();


private:
    int m_width_H = 400;
    int m_height_H = 400;

    int m_width_N = 300;
    int m_height_N = 300;

    GLFWwindow* m_window_T = nullptr;
    int m_width_T = 1600;
    int m_height_T = 900; 


    unsigned int m_ColorShaderProgram = 0;
    unsigned int m_ColorVAO = 0;

    unsigned int m_NoiseShaderProgram = 0;
    unsigned int m_NoiseVAO = 0;

    unsigned int m_CompositionShaderProgram = 0;
    unsigned int m_CompositionVAO = 0;

    unsigned int m_NoiseInterfConverterProgram = 0;

    unsigned int m_fbo_N1 = 0;
    unsigned int m_texture_N1 = 0;
    unsigned int m_fbo_N1_ui = 0;
    unsigned int m_texture_N1_ui = 0;

    unsigned int m_fbo_N2 = 0;
    unsigned int m_texture_N2 = 0;
    unsigned int m_fbo_N2_ui = 0;
    unsigned int m_texture_N2_ui = 0;

    unsigned int m_fbo_H = 0;
    unsigned int m_texture_H = 0;
    unsigned int m_fbo_T = 0;
    unsigned int m_texture_T = 0;

    bool m_n1_changed = false;
    bool m_n2_changed = false;

    float m_mean_N1;
    float m_mean_N2;
    float m_var_N1;
    float m_var_N2;

    std::vector<unsigned int> unif_locations;

    CCVT m_ccvt;
    unsigned m_size_density;
    float m_max_val;

    static const unsigned int m_MaxPointsNb = 30; // change in composition shader and color shader too
    unsigned int m_CurrentPointsNb;

    std::vector<point_info> m_points;
    std::vector<cell_info> m_cells;
    std::vector<histo_info> m_histo;

    std::vector<unsigned> m_adjGraph_id;
    bool m_showAdjGraph = false;

    selection m_selected;

    std::string m_infoBuffer{"", 100};
    std::vector<double> m_timer;


    float m_F1Princ = 16.;
    float m_F1Spread = 0.;
    float m_Or1Princ = 2.;
    float m_Or1Spread = 0.;

    float m_F2Princ = 20.;
    float m_F2Spread = 0.;
    float m_Or2Princ = 1.;
    float m_Or2Spread = 1.;
};


#endif //ASTEX_CCVT_APPLICATION_H
