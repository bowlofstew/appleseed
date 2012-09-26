
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2012 Francois Beaune, Jupiter Jazz Limited
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_STUDIO_MAINWINDOW_PROJECT_MATERIALASSIGNMENTEDITORWINDOW_H
#define APPLESEED_STUDIO_MAINWINDOW_PROJECT_MATERIALASSIGNMENTEDITORWINDOW_H

// appleseed.renderer headers.
#include "renderer/api/scene.h"

// appleseed.foundation headers.
#include "foundation/utility/containers/dictionary.h"

// Qt headers.
#include <QComboBox>
#include <QObject>
#include <QWidget>

// Standard headers.
#include <map>
#include <string>

// Forward declarations.
namespace Ui        { class MaterialAssignmentEditorWindow; }
class QGridLayout;
class QLineEdit;
class QPushButton;
class QString;
class QVBoxLayout;

namespace appleseed {
namespace studio {

class MaterialAssignmentEditorWindow
  : public QWidget
{
    Q_OBJECT

  public:
    MaterialAssignmentEditorWindow(
        QWidget*                        parent,
        renderer::ObjectInstance&       object_instance);

    ~MaterialAssignmentEditorWindow();

  signals:
    void signal_accepted(foundation::Dictionary values);

  private:
    // Not wrapped in std::auto_ptr<> to avoid pulling in the UI definition code.
    Ui::MaterialAssignmentEditorWindow* m_ui;

    renderer::ObjectInstance&           m_object_instance;

    typedef renderer::ObjectInstance::Side Side;

    struct SlotInfo
    {
        std::string     m_slot_name;
        Side            m_side;
        QComboBox*      m_combo_box;
        QLineEdit*      m_line_edit;

        QString get_mode() const
        {
            return m_combo_box->itemData(m_combo_box->currentIndex()).toString();
        }
    };

    typedef std::map<QPushButton*, SlotInfo> SlotInfoCollection;

    std::map<QComboBox*, QWidget*>      m_model_combo_to_widget_group;
    SlotInfoCollection                  m_slot_infos;

    void create_widgets();

    void create_widgets_for_slot(
        QVBoxLayout*    parent,
        const char*     slot_name);

    void create_widgets_for_side(
        QGridLayout*    parent,
        const int       row_index,
        const char*     slot_name,
        const Side      side);

    static void append_row(
        QVBoxLayout*    parent,
        QLayout*        row_layout);

    void assign_materials();
    void assign_material(const SlotInfo& slot_info);
    void assign_material(
        const SlotInfo& slot_info,
        const QString&  material_name);

  private slots:
    void slot_change_back_material_mode(int index);
    void slot_open_entity_browser();
    void slot_entity_browser_accept(QLineEdit* line_edit, QString page_name, QString entity_name);
    void slot_accept();
};

}       // namespace studio
}       // namespace appleseed

#endif  // !APPLESEED_STUDIO_MAINWINDOW_PROJECT_MATERIALASSIGNMENTEDITORWINDOW_H