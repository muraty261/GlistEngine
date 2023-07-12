/*
 * Copyright (C) 2016 Nitra Games Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ENGINE_GRAPHICS_GIMAGE_H_
#define ENGINE_GRAPHICS_GIMAGE_H_

#include "gTexture.h"


/** gImage holds several functions primarily to locate and load images.
*
* Overview of the functions: load and loadImage functions to load images effectively.
* loadData and loadImageData functions to load image's Data in a separate
* thread. useData function to create the texture in VRAM by using the loaded data.
* setImageData function to alter an image's data in integer format. setImageDataHDR
* function to alter an image's data in float format. getImageData function to  access
* an image's original or edited data in integer format. getImageDataHDR function to
* access an image's original or edited data in float format. clearData function to clear
* a given Data.
*/
class gImage : public gTexture {
public:
	gImage();
	gImage(int w, int h, int format = GL_RGBA);
	virtual ~gImage();

	/**
   * Loads an image from the given fullpath.
   *
   * Supported image formats can be found in the class description.
   *
   * The image might be stored anywhere on the hard disk or other storage
   * devices out of the project folder.
   *
   * This function was created primarily for development purposes. Due to the
   * difficulties and errors of storing images in a messy fashion, developers
   * are encouraged to use the loadImage function instead.
   *
   * @param fullPath The full path to the image file. It should contain the
   * full path of the folder where the image is located, the name of the image
   * and its extension. It is case sensitive.
   *
   * @return Image id number generated by OpenGL.
   */
	unsigned int load(const std::string& fullPath);

	/**
   * Loads an image from the project's images folder.
   *
   * Supported image formats can be found in the class description.
   *
   * There is no need to enter the folder address, as the function loads from
   * the project's own images folders. It is only necessary to specify the name
   * and extension of the image. For example, giving an address such as "image.jpg"
   * is sufficient. Make sure that the named image is placed in the project's
   * images folder.
   *
   * Project's default images folder is ProjectLocation/assets/images directory.
   *
   * The project's image folder may vary depending on the project's scaling
   * settings. In case of SCALING_NONE and SCALING_AUTO, this function loads images
   * from ProjectLocation/assets/images folder. In case of SCALING_MIPMAP,
   * ProjectLocation/assets/mipmaps/DeviceResolution folder becomes images folder.
   *
   * Developers are encouraged to use this function for image loading so that an
   * efficient and shareable work can be carried out.
   *
   * @param imagePath The fullname of the image stored under project's images
   * folder. Fullname should contain image name and its extension. It is case
   * sensitive.
   *
   * @return Image id number generated by OpenGL.
   */
	unsigned int loadImage(const std::string& imagePath);

	unsigned int loadImageFromURL(const std::string& imageUrl);
	unsigned int loadImageFromURL(const std::string& imageUrl, bool cutUrlParameters);

	/**
  * Loads an image's data from the given full path to the RAM.
  *
  * Supported image formats can be found in the class description.
  *
  * The image can be located in anywhere(hard disk or other storage devices)
  * as long as it has the full path.Supported image formats can be found in the class
  * description.
  *
  * Loading assets in separate threads improves overall efficiency. In order to load
  * an image's data separately, this function can be used. It doesn't create a texture
  * of the loaded data's image in VRAM, instead it loads the Data of a given image
  * and saves it into the RAM.
  *
  * @param fullPath  The full path to the image file. It should contain the
  * full path of the folder where the image is located.
  *
  */
	void loadData(const std::string& fullPath);

	/**
  * Loads an image's data from the project's images folder to the RAM.
  *
  * Supported image formats can be found in the class description.
  *
  * It doesn't require a full path of an image because the function loads an image
  * from the project's own images folders. In fact, providing this function with a
  * path that looks like 'image.jpg' is sufficient.
  *
  * Project's default images folder is ProjectLocation/assets/images directory.
  *
  * Loading assets in separate threads improves overall efficiency. In order to load
  * an image's data separately, this function can be used. It doesn't create a texture
  * of the loaded data's image in VRAM, instead it loads the Data of a given image
  * and saves it into the RAM.
  *
  * Developers are encouraged to use this function for Data loading so that an
  * efficient work can be carried out.
  *
  * @param ImagePath  The full name of the image stored under project's images
  * folder which should contain the image name and its extension. It is case
  * sensitive.
  */
	void loadImageData(const std::string& imagePath);

	/**
  * Creates a texture in VRAM by the usage of loaded data.
  */
	unsigned int useData();

	/**
  * Alters an image's data in integer format.
  *
  * Data of a given image can be altered by the usage of this function.
  * It's in integer format.
  */
	void setImageData(unsigned char* imageData);

	void setImageData(unsigned char* imageData, int width, int height, int componentNum);

	/**
  * Accesses an image's original or edited data in integer format.
  * The data should be loaded in order to be accessed by this function.
  */
	unsigned char* getImageData();

	/**
  * Alters an image's data in float format.
  *
  * Data of a given image can be altered by the usage of this function.
  * It's in float format.
  */
	void setImageDataHDR(float* imageData);

	/**
  * Accesses an image's original or edited data in float format.
  * The data should be loaded in order to be accessed by this function.
  */
	float* getImageDataHDR();

	/**
  * Clears the data of a given structure.
  */
	void clearData();

	/**
   * Used for the image's extension and changing image's name.
   *
   * @param fileName is a string value  for the function .
   * This file will be exist in the GlistApp's assets clasor
   * after saving process.
   */
	void saveImage(std::string fileName);

	std::string getImageUrl();
	static std::string generateDownloadedImagePath(std::string imageType = "png");
	unsigned int loadMaskImage(const std::string& maskImagePath);

private:
	bool loadedfromurl;
	std::string imageurl;
	static int downloadno;
};

#endif /* ENGINE_GRAPHICS_GIMAGE_H_ */
