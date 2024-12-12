void Cutscene::indexScript() {
  if(!hasIndexedScript) {
    scriptLine.clear();
    switch(sceneID) {
    case hg1:
      scriptLine.push_back("hi xDxdxdXdxXD");
      break;
    }
  }
  totalNumberOfLines = scriptLine.size();
  hasIndexedScript = true;
}
