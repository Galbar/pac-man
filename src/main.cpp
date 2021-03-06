#include "GamePlugin.hpp"
#include "GameGlobals.hpp"





int main(void) {
  Game g;

  // add media manager
  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.antialiasingLevel = 4;
  settings.majorVersion = 3;
  settings.minorVersion = 3;
  auto mogl = g.addPlugin<MultimediaOGL>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
    "Pac-man", sf::Style::Default, settings);

  // custom shaders
  Shader* vertexShader = new Shader();
  vertexShader->loadFromSource(Shader::Type::VERTEX_SHADER, 
    #include "../shaders/basic.vert"
  );  
  Shader* fragmentShader = new Shader();
  fragmentShader->loadFromSource(Shader::Type::FRAGMENT_SHADER, 
    #include "../shaders/basic.frag"
  );
  
  ShaderProgramManager* shaderManager = &mogl->shaderPrograms();
  shaderManager->load("_pac_basic", { *vertexShader, *fragmentShader, "out_color" });

  // default camera
  mogl->getCamera().setOrthogonal(-9, 9, -9, 9);
  mogl->getCamera().setPosition(glm::vec3(10, 10, 10));
  mogl->getCamera().setCenter(glm::vec3(0, 0, 0));
  mogl->getCamera().setUp(glm::vec3(0, 1, 0));


  // add game manager
  //g.addPlugin<KinematicWorld>();
  g.addPlugin<GamePlugin>();

  // loop
  g.run();
  return 0;
}
