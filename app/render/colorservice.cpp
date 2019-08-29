#include "colorservice.h"

#include "common/define.h"

ColorService::ColorService(const char* source_space, const char* dest_space)
{
  OCIO::ConstConfigRcPtr config = OCIO::GetCurrentConfig();

  processor = config->getProcessor(source_space,
                                   dest_space);
}

void ColorService::Init()
{
  // FIXME: Hardcoded values for testing purposes
  OCIO::ConstConfigRcPtr config = OCIO::Config::CreateFromFile("/run/media/matt/Home/OpenColorIO/ocio.configs.0.7v4/nuke-default/config.ocio");

  OCIO::SetCurrentConfig(config);
}

ColorServicePtr ColorService::Create(const char *source_space, const char *dest_space)
{
  return std::make_shared<ColorService>(source_space, dest_space);
}

void ColorService::ConvertFrame(FramePtr f)
{
  OCIO::PackedImageDesc img(reinterpret_cast<float*>(f->data()), f->width(), f->height(), kRGBAChannels);

  processor->apply(img);
}

OpenColorIO::v1::ConstProcessorRcPtr ColorService::GetProcessor()
{
  return processor;
}