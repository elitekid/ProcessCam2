// Copyright 2024 elitekid

#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include <glad/glad.h>

#include <iostream>

class IndexBuffer {
 public:
  IndexBuffer();
  ~IndexBuffer();
  void DeleteIndexBuffer();
  void CreateIndexBuffer(const unsigned int* data, unsigned int count);
  void Bind() const;
  void Unbind() const;

 private:
  unsigned int ib_id_;
  unsigned int count_;
};

#endif  // INDEX_BUFFER_H_