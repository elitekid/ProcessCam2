// Copyright 2024 elitekid

#ifndef VERTEX_BUFFER_LAYOUT_H_
#define VERTEX_BUFFER_LAYOUT_H_

#include <glad/glad.h>

#include <cassert>
#include <iostream>
#include <vector>

struct VertexBufferElement {
 public:
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int GetSizeOfType(unsigned int type) {
    switch (type) {
      case GL_FLOAT:
        return 4;
      case GL_UNSIGNED_INT:
        return 4;
      case GL_UNSIGNED_BYTE:
        return 1;
      default:
        assert(false);
        return 0;
    }
  }
};

class VertexBufferLayout {
 public:
  VertexBufferLayout();
  void AddFloat(unsigned int count);
  void AddUnsignedInt(unsigned int count);
  void AddUnsignedChar(unsigned int count);

  inline const std::vector<VertexBufferElement>& GetElements() const {
    return elements_;
  }
  inline unsigned int GetStride() const {
    return stride_; 
  }

 private:
  std::vector<VertexBufferElement> elements_;
  unsigned int stride_;
  void Push(unsigned int type, unsigned int count, unsigned char normalized);
};

#endif  // VERTEX_BUFFER_LAYOUT_H_
