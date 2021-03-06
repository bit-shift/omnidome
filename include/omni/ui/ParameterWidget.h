/* Copyright (c) 2014-2015 "Omnidome" by cr8tr
 * Dome Mapping Projection Software (http://omnido.me).
 * Omnidome was created by Michael Winkelmann aka Wilston Oreo (@WilstonOreo)
 * 
 * This file is part of Omnidome.
 * 
 * Omnidome is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OMNI_UI_PARAMETERWIDGET_H_
#define OMNI_UI_PARAMETERWIDGET_H_

#include <set>
#include <QWidget>
#include <QCheckBox>
#include <slim/RangedFloat.h>
#include <slim/RangedInt.h>
#include <slim/Rotation.h>
#include <omni/util.h>

namespace omni
{
  namespace ui
  {
    /**@brief A widget which holds sub-widgets for manipulating parameters
    **/
    class ParameterWidget : public QWidget
    {
      Q_OBJECT
    public:
      /// Default constructor 
      ParameterWidget(QWidget* _parent = nullptr);
        
      /// Default Constructor  
      virtual ~ParameterWidget();

      /// Adds a widget with a name, a value and min-max range
      slim::RangedFloat* addWidget(QString const&,float,float,float);
      
      /// Adds a integer widget with a name, a value and min-max range
      slim::RangedInt* addIntegerWidget(QString const&,int,int,int);

      /// Adds an angle widget with a name, a value and min-max range
      slim::RangedFloat* addAngleWidget(QString const&,float,float,float);
        
      /// Adds an offset widget with a name, a value and min-max range
      slim::RangedFloat* addOffsetWidget(QString const&,float,float,float);

      /// Adds an Rotation widget with three dials for X,Y and Z axis
      slim::Rotation* addRotationWidget(QString const&);

      /// Adds a checkbox
      QCheckBox* addCheckBox(QString const&, bool _checked = false);

    public slots:
      /// Removes all parameter widgets
      void clear();

      virtual void updateParameters();
      
      /// Utility method for retrieving the value from a slider with id
      double getParamAsFloat(QString const&) const;
      
      /// Set slider value from given value
      void setParamAsFloat(QString const& _str, double _value);
      
      /// Utility method for retrieving the value from a slider with id
      int getParamAsInt(QString const&) const;
      
      /// Set slider value from given value
      void setParamAsInt(QString const& _str, int _value);

      /// Utility method for retrieving the value from checkbox with id
      bool getParamAsBool(QString const&) const;

      /// Get parameter widget from parameter map with Id
      QWidget* getWidget(QString const&);

      void setParametersVisible(bool);

    signals:
      void parametersUpdated();

    protected: 

      template<typename F>
      void locked(F f) 
      {
        bool _oldLocked = locked_;
        locked_ = true;
        f();
        locked_ = _oldLocked;
      }

      inline bool isLocked() const 
      {
        return locked_;
      }

      /// Slider parameter widgets
      std::vector<QUniquePtr<QWidget>> parameters_;
        
      /// Slider widgets, sorted by their label
      std::map<QString,QWidget*> parameterMap_;

    private:
      /// Flag which sets if widgets are currently locked
      bool locked_ = false;
    };
  }
}

#endif /* OMNI_UI_PARAMETERWIDGET_H_ */
