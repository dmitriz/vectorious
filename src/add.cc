#include <node.h>
#include "add.h"

void add(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::HandleScope scope(isolate);
  
  v8::Local<v8::Object> v1 = args[0]->ToObject();
  double* v1_data = static_cast<double*>(v1->GetIndexedPropertiesExternalArrayData());
  
  v8::Local<v8::Object> v2 = args[1]->ToObject();
  double* v2_data = static_cast<double*>(v2->GetIndexedPropertiesExternalArrayData());
  
  int byte_length = v1->Get(v8::String::NewFromUtf8(isolate, "byteLength"))->Uint32Value();
  int length = byte_length / sizeof(double);
  
  v8::Handle<v8::ArrayBuffer> array_buffer = v8::ArrayBuffer::New(isolate, byte_length);
  unsigned int array_byte_offset = array_buffer->Get(v8::String::NewFromUtf8(isolate, "byteOffset"))->Uint32Value();
  v8::Local<v8::Float64Array> result = v8::Float64Array::New(array_buffer, array_byte_offset, length);
  
  int i;
  for(i = 0; i < length; i++)
    result->Set(i, v8::Number::New(isolate, v1_data[i] + v2_data[i]));
  
  args.GetReturnValue().Set(result);
}