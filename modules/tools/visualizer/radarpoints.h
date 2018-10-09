/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef MODULES_TOOLS_VISUALIZER_RADARPOINTS_H_
#define MODULES_TOOLS_VISUALIZER_RADARPOINTS_H_

#include <QVector3D>
#include <QColor>
#include <QRgb>

#include "modules/tools/visualizer/renderable_object.h"
#include "modules/drivers/proto/radar.pb.h"

class QOpenGLShaderProgram;

class RadarPoints : public RenderableObject
{
    /* struct Point{
     *    GLfloat x, // raw data from radar
     *    GLfloat y,
     *    GLfloat r
     * };
     */

public:
    explicit RadarPoints(std::shared_ptr<QOpenGLShaderProgram> shaderProgram = nullptr);
    ~RadarPoints(void){
        if(buffer_){
            delete [] buffer_;
            buffer_ = nullptr;
        }
    }

    virtual GLenum GetPrimitiveType(void) const { return GL_POINTS; }

    void SetupExtraUniforms(void) {
      shader_program_->setUniformValue("color", color_);
    }

    GLfloat red(void) const { return color_.x(); }
    GLfloat green(void) const { return color_.y(); }
    GLfloat blue(void) const { return color_.z(); }

    const QVector3D& color(void) const { return color_; }

    void set_color(const QRgb& rgb){
        set_color(QColor(rgb));
    }

    void set_color(const QColor& color) {
        color_.setX(color.redF());
        color_.setY(color.greenF());
        color_.setZ(color.blueF());
    }

    bool FillData(
        const std::shared_ptr<const apollo::drivers::RadarObstacles>& pData);

protected:
    bool FillVertexBuffer(GLfloat* pBuffer) override;

private:

    QVector3D color_; // r, g, b
    GLfloat* buffer_;
};

#endif // MODULES_TOOLS_VISUALIZER_RADARPOINTS_H_
